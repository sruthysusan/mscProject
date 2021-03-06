 
#include "globalConstant.h"

#ifndef UART_H
#define UART_H

#define POWER_BUTTON PTA12 
#define ENABLE_BUTTON PTD4 

enum BTpos{NAME=0,ADDR,PSWD,VERSION,CMODE,LINK,ENUM_END,
           INIT,IAC,CLASS,RSSI_VAL,RSSI_REQ,ENUM_END_2};


class uartModem {
  
public:   
  
typedef uint32_t BAUD;
  
Serial *serialPort;  // keep as public for straight connection 

uint8_t rx_MsgBuffer[RX_LEN];

string myBtDetails[BT_REGISTER_SIZE];
string myBtQuerry [BT_REGISTER_SIZE];

uartModem (BAUD baudRate);
~uartModem();

void sendUartData( char* strData);  // data pointing by reference method
bool stackRxbuffer();

bool isRxdataReady();
void enableRxStatusFlag (bool enable);
void stackBTregisterDetails (int reqData=0,int reqLimit=(int)ENUM_END);  // normally perform all the data read
bool btresponseWait();
bool isCommandmode() {return at_CommandMode;}

uint8_t btResponseOK();
uint8_t stat,count;
  
/*___________________Private Sector of class starts here_________________________________*/


private:

uint8_t statusFLAG;
Timer rxExitTimer;
DigitalOut powerControl, enableControl;
bool at_CommandMode;

void loadBtQuerry(string* BtQuerry);

  /*  The Blue Tooth communication  functions */


uint8_t btresponseVersion();
uint8_t btresponsePassword();
uint8_t  btTwoResponseFunc( char* commandPayload, BTpos position );



void BT_power_ON (bool on);

public:
void BT_powerreset_Pushbtn(bool enable=false);
void atCommandMode(bool enable);

};

#endif
