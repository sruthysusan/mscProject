#include "RangeUltrasonic.h"
#include <algorithm>
//https://os.mbed.com/components/HC-SR04/

Rangingclass::Rangingclass (uint8_t brustTime):triggerTime (brustTime),
                                               hc04_Trigger(PTB1),hc04_Echo(PTB0)
{  
  t_timer.reset();  
  t_timer.start();
  while (hc04_Echo==2);  // wait for read time
  t_timer.stop(); 
  correction = t_timer.read_us();
}



 uint16_t Rangingclass :: rangeObstacle(uint16_t timeOut)
 {
  uint16_t Pulsar=0;
  uint8_t reTries = 4; // try 4 times incase of ERROR
  do
  {
  pStateEcho = hc04_Echo;
  t_timer.reset();  
  rise_fallTrigger(false,2);
  rise_fallTrigger(true,triggerTime);   // generating a trigger pulse
  rise_fallTrigger(false,0);  
  
  Pulsar = pulseIn( hc04_Echo, 0,timeOut );  // reading the Echo time slot
  }
  while (Pulsar == ERROR && reTries--);  // ERROR referes outofrange
  
  uint16_t distance = OUT_OF_RANGE; 
  if(reTries)                         // if a valid distance read happened
   {
     calculate_save_Dist(Pulsar);
     distance = rangeRecord[0];
   }  
  return distance;    // in centimeters
 }
 
 
 
 
 
void Rangingclass :: calculate_save_Dist( uint16_t Pulsar )
{
  uint8_t *RangeRecordEND = rangeRecord +sizeof(rangeRecord);
//https://stackoverflow.com/questions/1903190/optimal-way-to-perform-a-shift-operation-on-an-array
/*
Old array : 1 2 3 4 5 6 7 8 9
New new after 1 right rotation : 9 1 2 3 4 5 6 7 8
*/
  std::rotate( rangeRecord, (RangeRecordEND-1), RangeRecordEND );  //https://www.geeksforgeeks.org/stdrotate-in-c/    ;                                                   
  rangeRecord[0] = (Pulsar - correction) /58.0;    // compute distance in centimeters    
}
 
 
  uint16_t Rangingclass :: pulseIn(DigitalIn pin, bool value,uint16_t timeOut )
 {
    uint16_t loc_timeOut;
    loc_timeOut = timeOut;
  
    while( hc04_Echo == (int)pStateEcho )      // wait for the echo pulse
    {
      if(!(loc_timeOut--))
         return ERROR;
         wait_us(1);
    }
    
    t_timer.start();
    
    loc_timeOut = timeOut;
    while( hc04_Echo == (int)value )      // wait for the echo pulse
    {
      if(!(loc_timeOut--))
          return ERROR;
          wait_us(1);
    }
    
    loc_timeOut = timeOut;
    while( hc04_Echo == (int)!value )      // wait for the echo pulse
    {
      if(!(loc_timeOut--))
          return ERROR;
          wait_us(1);
    }
    loc_timeOut = t_timer.read_high_resolution_us();
    t_timer.stop();
    
    return( loc_timeOut);   // returning the Timer
 }
