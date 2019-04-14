#include "RangeUltrasonic.h"

//https://os.mbed.com/components/HC-SR04/

Rangingclass::Rangingclass (uint8_t brustTime):triggerTime (brustTime),
                                               hc04_Trigger(PTB1),hc04_Echo(PTB0)
{  
//  triggerTime = brustTime; 
//  hc04_Trigger = new DigitalOut(PTB1); 
//  hc04_Echo= new DigitalIn(PTB0);  
  t_timer.reset();  
  t_timer.start();
  while (hc04_Echo==2);
  t_timer.stop(); 
  correction = t_timer.read_us();
 // hc04_Echo=0;
}



 uint16_t Rangingclass :: rangeObstacle(uint16_t timeOut)
 {
  uint16_t i=0;
  pStateEcho = hc04_Echo;
  t_timer.reset();  
  rise_fallTrigger(false,2);
  rise_fallTrigger(true,triggerTime);   // generating a trigger pulse
  rise_fallTrigger(false,0);   
  
 /*
  while(*hc04_Echo ==k )      // wait for the echo pulse
  {}
  t_timer.start();
  while(*hc04_Echo ==0);
  
  while(*hc04_Echo ==1);
  
  
 k = t_timer.read_high_resolution_us();
 t_timer.stop(); 
 */
  return  uint16_t(pulseIn(hc04_Echo, 0,timeOut )- correction) /58.0;    // in centimeters
 // return  uint16_t(k- correction) /58.0;    // in centimeters
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
