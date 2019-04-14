#include "globalConstant.h"
// PTB0 and PTB1 for echo and trigger

/*
   Sound speed = 340m/sec ==> 100cms/3msec
*/
class Rangingclass {

private:
  
DigitalOut hc04_Trigger; 
DigitalIn  hc04_Echo;
Timer t_timer;      // just a timer module

int correction;
uint8_t triggerTime;
bool pStateEcho;

uint8_t rangeRecord[RECORDS];   // to save the range values
/*
// default timeout = 10,000 usec, time taking more than 9msec implies 
   obstacle @ more than 3 m away
*/

uint16_t pulseIn(DigitalIn pin, bool value,uint16_t timeOut );  
void calculate_save_Dist( uint16_t Pulsar );


void rise_fallTrigger(bool risePulse,uint16_t waitTime)
{
  hc04_Trigger = risePulse;
  wait_us(waitTime);
}

public:

 
Rangingclass(uint8_t brustTime);  
uint16_t  rangeObstacle(uint16_t timeOut =10000);
uint8_t UpdateRangeArray(uint8_t  position){ return rangeRecord[position];  }  
  
};