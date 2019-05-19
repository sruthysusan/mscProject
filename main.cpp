#include "UART.h"
#include "motorSpeed.h"
#include "RangeUltrasonic.h"
#include "CommunicationPrtcol.h"

void calc_Make_Send() ;
void rxCallback();
void manualPioloting();
void autoPioloting();
bool canImoveForward();

uartModem blueToothport(38400);
Communication_lib CommunicationLayer;
motorSetting MotorParams(NEUTRAL);
Rangingclass rangerObjt(10);
bool decessionExec;

// This function is called when a character goes into the RX buffer.


int main() 
{    

    blueToothport.serialPort->attach(&rxCallback, Serial::RxIrq);  
    wait(WARMUP_TIME);  // warm up time
    blueToothport.stackBTregisterDetails ();
    Ticker Datamaker_Send,autoPilot; 

    // blueToothport.stackBTregisterDetails (INIT,ENUM_END_2);
    
   blueToothport.atCommandMode(false);
   blueToothport.BT_powerreset_Pushbtn(true);
   

  Datamaker_Send.attach(&calc_Make_Send, 1.0); // function call @ every (1 seconds)
  
    while (1) {    

                 
    
        if( CommunicationLayer.RecvdData[0] == PACKET_START)   // if the data has been received
        {
          CommunicationLayer.RecvdData[0] = RESET;
           if(CommunicationLayer.RecvdData[AUTO_MAN_RSSI] == MANUAL)
           {
              manualPioloting();
              autoPilot.detach();
           }
           else 
           {
              autoPilot.attach_us(&autoPioloting, (800000*2)); //800msec
           }  
           
        }          
    }      
}


void autoPioloting()
  {
  if (canImoveForward())                 
    {
      MotorParams.engineDrivingParams (CommunicationLayer.RecvdData[SET_SPEED] ,FORWARD,NO_DIRECTION);
    }else
    {
      MotorParams.engineDrivingParams (SPEED_1 ,FORWARD,RIGHT_TURN);      
    }
  }


void calc_Make_Send() 
  {
   CommunicationLayer.roverParameters[RSSI] = (unsigned char)MotorParams.currentDirection;    
    
   CommunicationLayer.roverParameters[DIST_2_OBST] = rangerObjt.rangeObstacle();
   
   CommunicationLayer.roverParameters[GEAR] = (unsigned char)MotorParams.currentGear;
   
   int parameters[2] ={0,1};
   if (MotorParams.currentDirection == FORWARD) { parameters[0] =1; parameters[1] =0;}
        
   CommunicationLayer.roverParameters[ROV_SPEED]= ((rangerObjt.enquireRangeRecord_Pos(parameters[0])   
                                           -  rangerObjt.enquireRangeRecord_Pos(parameters[1]))/5);  // cms/sec (2 sec )
   
   CommunicationLayer.broadcastOutData(blueToothport);
  }


 


void manualPioloting()
{               
    uint16_t speed =  canImoveForward()? CommunicationLayer.RecvdData[SET_SPEED] : NEUTRAL;                        
    MotorParams.engineDrivingParams (speed ,(speed==REVERSE_SPEED),CommunicationLayer.RecvdData[L_R_STRAIGHT]);
}



bool canImoveForward(void) 
{
  bool success = false;
  
   if(rangerObjt.rangeObstacle() > CommunicationLayer.RecvdData[SET_OBSTACLE])
         success = true;
   
  return success;
}


void rxCallback() 
{    
  if( blueToothport.isCommandmode() )
       blueToothport.stackRxbuffer(); 
  else
       CommunicationLayer.ReceivedDataFunc(blueToothport);
}