 
#include "globalConstant.h"

#define POWER_BUTTON PTA12 
#define ENABLE_BUTTON PTD4 

enum BTpos{NAME=0,ADDR,PSWD,VERSION,ENUM_END};

class uartModem {
  
public:   
  
typedef uint32_t BAUD;
  
Serial *serialPort;  // keep as public for straight connection 

uint8_t rx_MsgBuffer[RX_LEN];

string myBtDetails[BT_REGISTER_SIZE];
string myBtQuerry [BT_REGISTER_SIZE];

uartModem (BAUD baudRate);
~uartModem();

void sendUartString(char* strData);  // data pointing by reference method
bool stackRxbuffer();

bool isRxdataReady();
void enableRxStatusFlag (bool enable);
void stackBTregisterDetails ();
bool btresponseWait();
uint8_t btResponseOK();
  
  
/*___________________Private Sector of class starts here_________________________________*/


private:

uint8_t statusFLAG;
uint8_t stat;
DigitalOut powerControl, enableControl;


void loadBtQuerry(string* BtQuerry);

  /*  The Blue Tooth communication  functions */


uint8_t btresponseVersion();
uint8_t btresponsePassword();
uint8_t  btTwoResponseFunc(char* commandPayload, BTpos position );


void BT_powerreset_Pushbtn(bool enable=false);
void atCommandMode(bool enable);
void BT_power_ON (bool on);

};

