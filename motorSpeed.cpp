#include "motorSpeed.h"

motorSetting :: motorSetting(SPEEDGEAR startSpeed):A1Apin(PTC1),A1Bpin(PTC2),B1Apin(PTB3),B1Bpin(PTB2)
{
  A1Apin.period(0.1);  // 10 msec pulse
  A1Bpin.period(0.1);
  B1Apin.period(0.1);
  B1Bpin.period(0.1);
}

void motorSetting :: engineDrivingParams (uint16_t gear, bool forwardMotion)
{
  //https://os.mbed.com/handbook/PwmOut
// float currentGear;// = (float(gear))/100;
 currentGear = gear;
 currentGear /=100;  // currentGear = currentGear/ 100;
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
}