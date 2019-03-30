#include "UART.h"



int main() {
uartModem blueToothport(38400);
  
//blueToothport.serialPort->attach(&callback);  //attach the process as an interrupt
    
while(1)
 {
        
        
       
wait(0.2);
   
    
}
}

void callback() 
{
  //  printf("%c\n", blueToothport.serialPort->getc());
}
