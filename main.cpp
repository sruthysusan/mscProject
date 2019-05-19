#include "UART.h"
#include "motorSpeed.h"
#include "RangeUltrasonic.h"
#include "CommunicationPrtcol.h"

void calc_Make_Send() ;
void rxCallback();

uartModem blueToothport(38400);
Communication_lib CommunicationLayer;
motorSetting MotorParams(NEUTRAL);
Rangingclass rangerObjt(10);



uint16_t dist, position;

int main() 
{    

    blueToothport.serialPort->attach(&rxCallback, Serial::RxIrq);  
 //   wait(WARMUP_TIME);  // warm up time
 //   blueToothport.stackBTregisterDetails ();
    Ticker Datamaker_Send; 

  //   blueToothport.stackBTregisterDetails (INIT,ENUM_END_2);
    
 //   MotorParams.engineDrivingParams (70 , 1);   //speed and direction ctrl
   blueToothport.atCommandMode(false);
   blueToothport.BT_powerreset_Pushbtn(true);
   char p[8];
 // wait(20);
  dist =150;
  Datamaker_Send.attach(&calc_Make_Send, 2.0); // function call @ every (1 seconds)
    while (1) {    

              
        dist -=5; 
     MotorParams.engineDrivingParams (dist , REVERSE,LEFT_TURN);
    
        if( CommunicationLayer.isRcvdDataRdy())   // if the data has been received
        {
         if(CommunicationLayer.RecvdData[AUTO_MAN_RSSI] == MANUAL)
         {
           // call function
         }
          
         
        }
       
    }
    
    

}


void calc_Make_Send() 
  {
   CommunicationLayer.roverParameters[RSSI] = (unsigned char)MotorParams.currentDirection;    
    
   CommunicationLayer.roverParameters[DIST_2_OBST] = rangerObjt.rangeObstacle();
   
   CommunicationLayer.roverParameters[GEAR] = (unsigned char)MotorParams.currentGear;
   
   int parameters[2] ={0,1};
   if (MotorParams.currentDirection == FORWARD)  parameters[0] =1; parameters[1] =0;
        
   CommunicationLayer.roverParameters[ROV_SPEED]= ((rangerObjt.enquireRangeRecord_Pos(parameters[0]) -  
                                               rangerObjt.enquireRangeRecord_Pos(parameters[1]))/2);  // cms/sec (2 sec )
   
   CommunicationLayer.broadcastOutData(blueToothport);
  }



// This function is called when a character goes into the RX buffer.
void rxCallback() 
{    
  if( blueToothport.isCommandmode() )
       blueToothport.stackRxbuffer(); 
  else
       CommunicationLayer.ReceivedData(blueToothport);
} 
