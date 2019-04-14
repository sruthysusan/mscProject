#include "UART.h"
#include "motorSpeed.h"
#include "RangeUltrasonic.h"
 
uartModem blueToothport(38400);

// This function is called when a character goes into the RX buffer.
void rxCallback() 
{     
   blueToothport.stackRxbuffer(); 
} 

  uint16_t dist;
int main() {    

    
    blueToothport.serialPort->attach(&rxCallback, Serial::RxIrq);
    wait(WARMUP_TIME);  // warm up time
    blueToothport.stackBTregisterDetails ();
    motorSetting MotorParams(NEUTRAL);
    Rangingclass rangerObjt(20);
    bool Dir;
 //   MotorParams.engineDrivingParams (70 , 1);
   
    while (1) {
    
    
      dist = rangerObjt.rangeObstacle();
      
        wait(2);

              
    
        
        if( blueToothport.isRxdataReady())   // if the data has been received
        {
          
          wait(2.5);
          wait(0.5);
        }
       
    }
}

