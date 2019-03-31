#include "UART.h"
 
uartModem blueToothport(38400);

// This function is called when a character goes into the RX buffer.
void rxCallback() 
{   
   
   
   blueToothport.stackRxbuffer();
   
    
    
} 

 
int main() {    

    
    blueToothport.serialPort->attach(&rxCallback, Serial::RxIrq);
 
    while (1) {
    
      char b[7];
     strcpy(b,"Hai");
     blueToothport.sendUartString("HAI");
        wait(2);
        
        if( blueToothport.isRxdataReady())
        {
          
          wait(2.5);
          wait(0.5);
        }
       
    }
}

