#include "UART.h"



uartModem::uartModem (BAUD baudRate)
   {
 //   serialPort->attach(&callback);  //attach the process as an interrupt
    t.start(callback(&eventQueue, &EventQueue::dispatch_forever));
    serialPort = new  Serial(USBTX, USBRX);    
    serialPort->baud(baudRate);
    serialPort->format(8,SerialBase::None,1);  
    serialPort->attach(&callback);
  }

uartModem::~uartModem ()
  {    
    delete serialPort;
  }

void uartModem:: callback() 
{
    printf("%c\n", serialPort->getc());
}
