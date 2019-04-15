#include "UART.h"
//#include "btCommands.h"
#include <string>

/*

              // Sample to verify

uint8_t uartModem :: btresponseVersion()
{     
  char* commandPayload ="AT+VERSION?\r\n";
  sendUartString(commandPayload);
  
  if(btresponseWait() == false)
   return false;                                                                // wait for the first set of incomes with /r
  
  myBtDetails[VERSION]=((char*)rx_MsgBuffer);  
  
          //http://www.cplusplus.com/reference/string/string/compare/
  
  if(!myBtDetails[VERSION].compare(1,strlen("+VERSION:"),"+VERSION:"))          // check first 8 characters
    {     
        //http://www.cplusplus.com/reference/string/string/substr/      
      myBtDetails[VERSION] = myBtDetails[VERSION].substr(strlen("+VERSION:"),
                             myBtDetails[VERSION].length() );                   // store the version number in without "+VERSION:"
    }
  if(btresponseWait() == false)
   return false;                                                                // wait for the first set of incomes with /r "OK"    
  
  if(strcmp((char*)rx_MsgBuffer,"OK\r"))
   return false;
 else
   return true;
}
*/

uint8_t uartModem :: btResponseOK()
{  
  bool Success = false;
  
  atCommandMode(true);                // activate enable pin of HC04 for AT mode
  BT_powerreset_Pushbtn(true);        // press push btn to power cycle BT module
  
  char* commandPayload ="AT\r\n";
  stat =1;
  sendUartString(commandPayload);
  
 if(btresponseWait() == false);
  // return false;
 
 if(strcmp((char*)rx_MsgBuffer,"OK\r\n"))
 {   
  // return false;
 }
 else
   Success = true;
 
   atCommandMode(false);             // deactivate enable pin of HC04 for AT mode
   BT_powerreset_Pushbtn(true);      // to simulate push btn press for BT power
  
  return Success;
}



uint8_t uartModem :: btTwoResponseFunc(char* commandPayload, BTpos position )
{
   bool Success = false;
  
  atCommandMode(true);                // activate enable pin of HC04 for AT mode
  BT_powerreset_Pushbtn(true);        // press push btn to power cycle BT module
 
    stat =2;
   sendUartString(commandPayload);
  
  if(btresponseWait() == false)
  {
  
    // return false;                       // wait for the first set of incomes with /r
} 
    myBtDetails[position]=((char*)rx_MsgBuffer);  
   
  int startPoint = myBtDetails[position].find(':');  // check for the ':' character
  if(startPoint ==  string::npos){}// refers noo ':' found
  //   return false;
    
//http://www.cplusplus.com/reference/string/string/compare/  
   if(myBtDetails[position].compare(1,startPoint,"ERROR")) // check first 8 characters and if not "ERROR"  
   {
//http://www.cplusplus.com/reference/string/string/substr/      
    myBtDetails[position] = myBtDetails[position].substr(startPoint+1,
                            myBtDetails[position].length());        // store the version number in without "+VERSION:"
//https://stackoverflow.com/questions/10392405/removing-everything-after-character-and-also-character
    myBtDetails[position] = myBtDetails[position].substr(0, myBtDetails[position].find('\r'));
   }
  
     atCommandMode(false);             // deactivate enable pin of HC04 for AT mode
   BT_powerreset_Pushbtn(true);      // to simulate push btn press for BT power
  
  return Success; 
}



bool uartModem :: btresponseWait()
{
  uint8_t timerFlag=0;
  
  while(!isRxdataReady())
  {
    wait_ms(10);  
    if(timerFlag++ > AT_WAIT_TIME)   
      break; 
  }
  
  if(timerFlag > AT_WAIT_TIME)
    return false;
  else
    return true;
}



void uartModem :: BT_power_ON (bool on)
{
   powerControl = on; 
}



void uartModem :: BT_powerreset_Pushbtn(bool enable)
{
  if(enable)
  {
     BT_power_ON(OFF);  // turn off BT for 100 msec 
     wait_ms(700);
  }
  BT_power_ON(ON);     //  and on
  wait_ms(700);
}


void uartModem ::atCommandMode (bool enable)
{
  count=0;
  enableControl = enable;
}