#include "UART.h"
#include "motorSpeed.h"
#include "RangeUltrasonic.h"
#include "CommunicationPrtcol.h"
 
uartModem blueToothport(38400);
Communication_lib normalCommunication;

// This function is called when a character goes into the RX buffer.
void rxCallback() 
{    
  if(blueToothport.isCommandmode())
     blueToothport.stackRxbuffer(); 
  else
    normalCommunication.ReceivedData();
} 

  uint16_t dist, position;
int main() 
{    

    blueToothport.serialPort->attach(&rxCallback, Serial::RxIrq);  
    wait(WARMUP_TIME);  // warm up time
    blueToothport.stackBTregisterDetails ();
    motorSetting MotorParams(NEUTRAL);
    Rangingclass rangerObjt(10);

     blueToothport.stackBTregisterDetails (INIT,ENUM_END_2);
    
 //   MotorParams.engineDrivingParams (70 , 1);   //speed and direction ctrl
   blueToothport.atCommandMode(false);
   blueToothport.BT_powerreset_Pushbtn(true);
  char p[8];
    while (1) {
    
 //  blueToothport.stat =1;
 //  dist = blueToothport.btResponseOK();
      
      
//      dist = rangerObjt.rangeObstacle();
//      position =  2;
   
   
    memcpy(p,"Haoi\r\n",sizeof(p));
   wait(0.5);
      blueToothport.sendUartString(p);
        

              
    
        
        if( blueToothport.isRxdataReady())   // if the data has been received
        {
          
          wait(2.5);
          wait(0.5);
        }
       
    }
}

