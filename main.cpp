#include "UART.h"


Serial *comPC;
uartModem blueToothport(38400,comPC);

int main() {

  
//blueToothport.serialPort->attach(&rxCallback, Serial::RxIrq);  //attach the process as an interrupt
    
while(1)
 {      
            
   wait(0.2);
     
 }
}






void rxCallback() 
{
   
    blueToothport.serialPort->putc(blueToothport.serialPort->getc());
}
