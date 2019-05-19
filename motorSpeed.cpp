#include "motorSpeed.h"

motorSetting :: motorSetting(SPEEDGEAR startSpeed)//:A1Apin(PTA5),A1Bpin(PTC2),B1Apin(PTB3),B1Bpin(PTB2)
{
   //PwmOut  A1Apin(PTA5),A1Bpin(PTC2),B1Apin(PTB3) ,B1Bpin(PTB2); 
  A1Apin = new PwmOut(PTC1);A1Bpin = new PwmOut(PTC2);B1Apin = new PwmOut(PTB3);B1Bpin = new PwmOut(PTB2);
  A1Apin->period(0.1);  // 10 msec pulse
  A1Bpin->period(0.1);
  B1Apin->period(0.1);
  B1Bpin->period(0.1);
  A1Apin->write (0); A1Bpin->write (0); B1Apin->write (0); B1Bpin->write (0);
}

void motorSetting :: engineDrivingParams (uint16_t gear, bool forwardMotion, uint8_t steerWheel)
{
  //https://os.mbed.com/handbook/PwmOut

 currentDirection =  forwardMotion;
 currentGear = gear;
 switch(gear)
 {
  case NEUTRAL: gear = 0; break;
  case SPEED_2: gear = 85; break;
  case SPEED_3: gear = 100; break;
  case SPEED_1:
  case REVERSE_SPEED: gear = 70; break;           
 } 
  
 
 float currentGearM = float(gear)/100;
// currentGear /=100;  // currentGear = currentGear/ 100;
switch(steerWheel)
 {

  case NO_DIRECTION: 
    if(forwardMotion)
    {    
  //set the motor direction on (gpio)
      A1Apin->write (currentGearM);
      A1Bpin->write (0);
      B1Apin->write (currentGearM);
      B1Bpin->write (0);
    }  
    else
    {
  //set the reverse direction on (gpio)
     A1Apin->write (0);
     A1Bpin->write (currentGearM);
     B1Apin->write (0);
     B1Bpin->write (currentGearM);
    }
  break;
  
  
  case RIGHT_TURN: 
    if(forwardMotion)
    {    
      A1Apin->write (currentGearM);
      A1Bpin->write (0);
      B1Apin->write (0);
      B1Bpin->write (0);
    }  
    else
    {
     A1Apin->write (0);
     A1Bpin->write (currentGearM);
     B1Apin->write (0);
     B1Bpin->write (0);
    }
  break;

  case LEFT_TURN: 
    if(forwardMotion)
    {    
  //set the motor direction on (gpio)
      A1Apin->write (0);
      A1Bpin->write (0);
      B1Apin->write (currentGearM);
      B1Bpin->write (0);
    }  
    else
    {
  //set the reverse direction on (gpio)
     A1Apin->write (0);
     A1Bpin->write (0);
     B1Apin->write (0);
     B1Bpin->write (currentGearM);
    }
  break;

 }
}