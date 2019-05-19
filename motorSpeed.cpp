#include "motorSpeed.h"

motorSetting :: motorSetting(SPEEDGEAR startSpeed):A1Apin(PTA4),A1Bpin(PTA5),B1Apin(PTB3),B1Bpin(PTB2)
{
  A1Apin.period(0.1);  // 10 msec pulse
  A1Bpin.period(0.1);
  B1Apin.period(0.1);
  B1Bpin.period(0.1);
}

void motorSetting :: engineDrivingParams (uint16_t gear, bool forwardMotion, uint8_t steerWheel)
{
  //https://os.mbed.com/handbook/PwmOut
// float currentGear;// = (float(gear))/100;
 currentDirection =  forwardMotion;
 currentGear = gear;
 currentGear /=100;  // currentGear = currentGear/ 100;
switch(steerWheel)
 {

  case NO_DIRECTION: 
    if(forwardMotion)
    {    
  //set the motor direction on (gpio)
      A1Apin.write (currentGear);
      A1Bpin.write (0);
      B1Apin.write (currentGear);
      B1Bpin.write (0);
    }  
    else
    {
  //set the reverse direction on (gpio)
     A1Apin.write (0);
     A1Bpin.write (currentGear);
     B1Apin.write (0);
     B1Bpin.write (currentGear);
    }
  break;
  
  
  case RIGHT_TURN: 
    if(forwardMotion)
    {    
      A1Apin.write (currentGear);
      A1Bpin.write (0);
      B1Apin.write (0);
      B1Bpin.write (0);
    }  
    else
    {
     A1Apin.write (0);
     A1Bpin.write (currentGear);
     B1Apin.write (0);
     B1Bpin.write (0);
    }
  break;

  case LEFT_TURN: 
    if(forwardMotion)
    {    
  //set the motor direction on (gpio)
      A1Apin.write (0);
      A1Bpin.write (0);
      B1Apin.write (currentGear);
      B1Bpin.write (0);
    }  
    else
    {
  //set the reverse direction on (gpio)
     A1Apin.write (0);
     A1Bpin.write (0);
     B1Apin.write (0);
     B1Bpin.write (currentGear);
    }
  break;

 }
}