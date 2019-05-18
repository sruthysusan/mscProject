#include "UART.h"
//#include "btCommands.h"


uartModem ::uartModem (BAUD baudRate) : powerControl(POWER_BUTTON),
                                        enableControl(ENABLE_BUTTON)
   { 
     
    serialPort = new  Serial(USBTX, USBRX);    
    serialPort->baud(baudRate);
    serialPort->format(8,SerialBase::None,1);  
    
    statusFLAG =0;
    memset(myBtDetails,'\0',sizeof(*myBtDetails) * BT_REGISTER_SIZE); // clearing all the detsails 
    BT_power_ON(OFF);     // turn off BT module
    loadBtQuerry(myBtQuerry);
    at_CommandMode = false;
  }



uartModem ::~uartModem ()
  {    
    delete serialPort;
  }
 


void uartModem :: sendUartString(char* strData)
 {
   unsigned i;  
   for( i=0; strData[i]!='\0'; i++ )     
     this->serialPort->putc(strData[i]);  
   //  this->serialPort->getc(); 
 }



bool uartModem :: stackRxbuffer()
{
 // static uint8_t count;
  
  if(count ==0)
  {
   rxExitTimer.start();
   memset(rx_MsgBuffer,'\0',RX_LEN);
  }
  rx_MsgBuffer[count] = serialPort->getc();
  if( rx_MsgBuffer[count] == RX_TERMINATOR && (!(--stat)) )
  {    
    rxExitTimer.stop();  rxExitTimer.reset();
    stat =1;
    count=0;  // reset count for new count
    enableRxStatusFlag(true);
    return true;
  }
  count++;
  if(count > RX_LEN || rxExitTimer.read() ==1)
  {
      count=0;  // reset count to normal
  }
  return false;
}



bool uartModem :: isRxdataReady()
{
  if (statusFLAG & RX_FLAG)
  {
    /* if the data buffer is filled up with values*/
    enableRxStatusFlag(false);   // clear the status flag
    return true;
  }
    return false;
}



void uartModem :: enableRxStatusFlag (bool enable)
{
  if(enable)
  statusFLAG |= (RX_FLAG);
  else 
  statusFLAG&= ~(RX_FLAG);
}



void uartModem :: stackBTregisterDetails (int reqData,int reqLimit)
{
  char p[25]={0};
  
  atCommandMode(true); // activate enable pin of HC04 for AT mode
  BT_powerreset_Pushbtn(true);
  if (btResponseOK())  // to see "AT" and "OK" command 
  {
   for(int i=reqData;i< reqLimit;i++)
   {     
// https://stackoverflow.com/questions/2889421/how-to-copy-a-string-into-a-char-array-in-c-without-going-over-the-buffer/2889483
     myBtQuerry[i].copy(p,myBtQuerry[i].length());
     btTwoResponseFunc(p, BTpos (i) );
   }
  }
  
  atCommandMode(false); // deactivate enable pin of HC04 for AT mode
  BT_powerreset_Pushbtn(true);  // to simulate push btn press for BT power
}




void uartModem :: loadBtQuerry(string* BtQuerry)
{
  BtQuerry[NAME]    = "AT+NAME?\r\n";
  BtQuerry[ADDR]    = "AT+ADDR?\r\n";
  BtQuerry[PSWD]    = "AT+PSWD?\r\n";
  BtQuerry[VERSION] = "AT+VERSION?\r\n";
  BtQuerry[CMODE] = "AT+CMODE=0\r\n";
  BtQuerry[LINK] = "AT+BIND=18,91,d6be4d\r\n";
  
  BtQuerry[INIT] = "AT+INIT\r\n";
  BtQuerry[IAC] = "AT+IAC=9e8b33\r\n";
  BtQuerry[CLASS] = "AT+CLASS=0\r\nAT\r\n";
  BtQuerry[RSSI_VAL] = "AT+INQM=1,1,48\r\n";
  BtQuerry[RSSI_REQ] = "AT+INQ\r\n";
}

