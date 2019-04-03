#include "UART.h"
#include "btCommands.h"
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



uint8_t uartModem :: btresponseVersion()

{     
  char* localStrToChk  = "+VERSION:";
  
  char* commandPayload ="AT+VERSION?\r\n";
  sendUartString(commandPayload);
  
  if(btresponseWait() == false)
   return false;                                                                // wait for the first set of incomes with /r
  
  myBtDetails[VERSION]=((char*)rx_MsgBuffer);  
  
          //http://www.cplusplus.com/reference/string/string/compare/
  
  if(!myBtDetails[VERSION].compare(1,strlen(localStrToChk),localStrToChk))          // check first 8 characters
    {     
        //http://www.cplusplus.com/reference/string/string/substr/      
      myBtDetails[VERSION] = myBtDetails[VERSION].substr( strlen(localStrToChk),
                             myBtDetails[VERSION].length() );                   // store the version number in without "+VERSION:"
    }
  if(btresponseWait() == false)
   return false;                                                                // wait for the first set of incomes with /r "OK"    
  
  if(strcmp((char*)rx_MsgBuffer,"OK\r"))
   return false;
 else
   return true;
}



uint8_t uartModem :: btresponsePassword()

{  
  char* localStrToChk  = "+PSWD:";
  char* commandPayload ="AT+PSWD?\r\n";
  
  sendUartString(commandPayload);
  
  if(btresponseWait() == false)
   return false;                                                                // wait for the first set of incomes with /r
  
  myBtDetails[PSWD]=((char*)rx_MsgBuffer);  
  
          //http://www.cplusplus.com/reference/string/string/compare/
  
  if(!myBtDetails[PSWD].compare(1,strlen(localStrToChk),localStrToChk))          // check first 8 characters
    {     
        //http://www.cplusplus.com/reference/string/string/substr/      
      myBtDetails[PSWD] = myBtDetails[PSWD].substr(strlen(localStrToChk),
                             myBtDetails[PSWD].length() );                   // store the version number in without "+VERSION:"
    }
  
  if(btresponseWait() == false)
   return false;                                                                // wait for the first set of incomes with /r "OK"    
  
  if(strcmp((char*)rx_MsgBuffer,"OK\r"))
   return false;
 else
   return true;
}

uint8_t uartModem :: btTwoResponseFunc(char* commandPayload, BTpos position )
{
   sendUartString(commandPayload);
  
  if(btresponseWait() == false)
   return false;                                                                // wait for the first set of incomes with /r
  
    myBtDetails[position]=((char*)rx_MsgBuffer);  
   
    int startPoint = myBtDetails[position].find(':');                     // check for the ':' character
    if(startPoint ==  string::npos)
         return false;
    
          //http://www.cplusplus.com/reference/string/string/compare/
  
   if(myBtDetails[position].compare(1,startPoint,"ERROR"))                     // check first 8 characters and if not "ERROR"  
   {
        //http://www.cplusplus.com/reference/string/string/substr/      
    myBtDetails[position] = myBtDetails[position].substr(startPoint,
                                        myBtDetails[position].length());        // store the version number in without "+VERSION:"
   }
   
  if(btresponseWait() == false)
   return false;                                                                // wait for the first set of incomes with /r "OK"    
  
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
    wait(0.1);  
    if(timerFlag++ > AT_WAIT_TIME)   
       break; 
  }
  if(timerFlag > AT_WAIT_TIME)
    return false;
  else
    return true;
}