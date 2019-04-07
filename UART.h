 
#include "globalConstant.h"

enum BTpos{NAME=0,ADDR,PSWD,VERSION,ENUM_END};

class uartModem {
  
public:   
  
typedef uint32_t BAUD;
  
Serial *serialPort;  // keep as public for straight connection 

uint8_t rx_MsgBuffer[RX_LEN];

string myBtDetails[BT_REGISTER_SIZE];
string myBtQuerry[BT_REGISTER_SIZE];

uartModem (BAUD baudRate);
~uartModem();

void sendUartString(char* strData);  // data pointing by reference method
bool stackRxbuffer();

bool isRxdataReady();
void enableRxStatusFlag (bool enable);
void stackBTregisterDetails ();



private:

uint8_t statusFLAG;
void loadBtQuerry(string* BtQuerry);

  /*  The Blue Tooth communication  functions */

uint8_t btResponseOK();
uint8_t btresponseVersion();
uint8_t btresponsePassword();

uint8_t  btTwoResponseFunc(char* commandPayload, BTpos position );

bool btresponseWait();

};

