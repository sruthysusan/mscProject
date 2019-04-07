#include "UART.h"
#include "motorSpeed.h"

 
uartModem blueToothport(38400);

// This function is called when a character goes into the RX buffer.
void rxCallback() 
{     
   blueToothport.stackRxbuffer(); 
} 

 
int main() {    

    
    blueToothport.serialPort->attach(&rxCallback, Serial::RxIrq);
    wait(WARMUP_TIME);  // warm up time
    blueToothport.stackBTregisterDetails ();
    motorSetting MotorParams(NEUTRAL);
    while (1) {
    

    
        wait(2);
        
        for(uint8_t i=0;i<100;i = i+3)
        {
          MotorParams.engineDrivingParams (i , 1);
       //   wait(0.3);
        }
        wait(2);
      for(uint8_t i=0;i<100;i = i+2)
        {
          MotorParams.engineDrivingParams (i , 0);
          wait(0.3);
        }  
        
        
        
        if( blueToothport.isRxdataReady())   // if the data has been received
        {
          
          wait(2.5);
          wait(0.5);
        }
       
    }
}

