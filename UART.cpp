#include "UART.h"



 uartModem ::uartModem (BAUD baudRate,Serial* comPort)
 
   { 
    serialPort = new  Serial(USBTX, USBRX);    
    serialPort->baud(baudRate);
    serialPort->format(8,SerialBase::None,1);  
    memcpy(comPort,serialPort,sizeof(serialPort));
  }

uartModem ::~uartModem ()
  {    
    delete serialPort;
  }

