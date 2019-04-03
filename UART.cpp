#include "UART.h"
//#include "btCommands.h"


 uartModem ::uartModem (BAUD baudRate) 
   { 
    serialPort = new  Serial(USBTX, USBRX);    
    serialPort->baud(baudRate);
    serialPort->format(8,SerialBase::None,1);  
    statusFLAG =0;
    memset(myBtDetails,'\0',sizeof(*myBtDetails) * BT_REGISTER_SIZE); // clearing all the detsails 
    loadBtQuerry(myBtQuerry);
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
 }

bool uartModem :: stackRxbuffer()
{
  static uint8_t count;
  
//   if( serialPort->getc() == '\n')
//      return false;
   
  rx_MsgBuffer[count] = serialPort->getc();
  if(rx_MsgBuffer[count] == '\r')
  {    
    count=0;  // reset count for new count
    enableRxStatusFlag(true);
    return true;
  }
  //(statusFLAG&= ~(RX_FLAG));
  count++;
  if(count > RX_LEN)  count=0;  // reset count to normal
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



void uartModem :: stackBTregisterDetails ()
{
  char p[25]={0};
  if (btResponseOK())  // to see "AT" and "OK" command 
  {
   for(int i=0;i< ENUM_END;i++)
   {     
// https://stackoverflow.com/questions/2889421/how-to-copy-a-string-into-a-char-array-in-c-without-going-over-the-buffer/2889483
     myBtQuerry[i].copy(p,myBtQuerry[i].length());
     btTwoResponseFunc(p, BTpos (i) );
   }
  } 
}



void uartModem :: loadBtQuerry(string* BtQuerry)
{
  BtQuerry[NAME]    = "AT+NAME?\r\n";
  BtQuerry[ADDR]    = "AT+ADDR?\r\n";
  BtQuerry[PSWD]    = "AT+PSWD?\r\n";
  BtQuerry[VERSION] = "AT+VERSION?\r\n";
}

