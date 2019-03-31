#include "UART.h"
#include "btCommands.h"
#include <string>

bool uartModem :: btResponseOK()
{
  
  char* commandPayload ="AT\r";
  sendUartString(commandPayload);
  
 if(btresponseWait() == false)
   return false;
 
 if(strcmp((char*)rx_MsgBuffer,"OK\r"))
 {
   
   return false;
 }
 else
   return true;
}



bool uartModem :: btresponseVersion()
{    
  char* commandPayload ="AT+VERSION?\r";
  sendUartString(commandPayload);
  
  if(btresponseWait() == false)
   return false;                  // wait for the first set of incomes with /r
 
  if(btresponseWait() == false)
   return false;                  // wait for the first set of incomes with /r "OK"
  
  if(strcmp((char*)rx_MsgBuffer,"OK\r"))
   return false;
 else
   return true;

}



bool uartModem :: btresponseWait()
{
  uint8_t timerFlag=0;
  while(!isRxdataReady())
  {
    wait(.1);  
    if(timerFlag++ > 19)   
       return false; 
  }
  return true;
}