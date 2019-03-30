#include "mbed.h"
 

class uartModem {
  
public: 
  
Serial *serialPort;  // keep as public for straight connection 
typedef uint32_t BAUD;

uartModem (BAUD baudRate,Serial* comPort);
~uartModem();

void sendUart();
void callbackM() ;

void rxCallback() 
{
   
   serialPort->putc(serialPort->getc());
}


private:
  


};