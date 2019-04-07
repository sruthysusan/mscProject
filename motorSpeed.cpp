#include "motorSpeed.h"

motorSetting :: motorSetting(SPEEDGEAR startSpeed):A1Apin(PTC1),A1Bpin(PTC2),B1Apin(PTB3),B1Bpin(PTB2)
{
  A1Apin.period(0.01);
  A1Bpin.period(0.01);
  B1Apin.period(0.01);
  B1Bpin.period(0.01);
//  Speedester = new PwmOut(PTD2); //https://www.youtube.com/watch?v=J5lsM1k-r-g 
//  Speedester->period(0.01);
//  *Speedester = startSpeed;
  // set the gpio's ready L9110S motor driver
 // DigitalOut A1Apin(PTC1),A1Bpin(PTC2),B1Apin(PTB3),B1Bpin(PTB2);
  
}

void motorSetting :: engineDrivingParams (uint16_t gear, bool forwardMotion)
{
// float currentGear;// = (float(gear))/100;
 currentGear = gear;
 currentGear /=100;
  if(forwardMotion)
  {
    //    set the motor direction on (gpio)
   // A1Apin = currentGear;
   // A1Bpin = 0;
    B1Apin = currentGear;
    B1Bpin = 0;
  }
  
  else
  {
    // set the reverse direction on (gpio)
  //  A1Apin = 0;
  //  A1Bpin = 1;
  //  B1Apin = currentGear;
  //  B1Bpin = 1-currentGear;
  }
 // *Speedester = gear;
  
}