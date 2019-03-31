#include "UART.h"



 uartModem ::uartModem (BAUD baudRate) 
   { 
    serialPort = new  Serial(USBTX, USBRX);    
    serialPort->baud(baudRate);
    serialPort->format(8,SerialBase::None,1);  
    statusFLAG =0;
  }

uartModem ::~uartModem ()
  {    
    delete serialPort;
  }
 
void uartModem :: sendUartString(char* strData)
 {
   unsigned i;  
   for( i=0; strData[i]!='\0'; i++ )     
     serialPort->putc(strData[i]);   
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