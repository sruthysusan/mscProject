#include "mbed.h"
#include <string> 
#include "globalConstant.h"

class uartModem {
  
public:   

Serial *serialPort;  // keep as public for straight connection 
typedef uint32_t BAUD;
uint8_t rx_MsgBuffer[RX_LEN];

string myDetails[BT_REGISTER_SIZE];

uartModem (BAUD baudRate);
~uartModem();

void sendUartString(char* strData);  // data pointing by reference method
bool stackRxbuffer();

bool isRxdataReady();
void enableRxStatusFlag (bool enable);
void stackBTregisterDetails ();



private:

uint8_t statusFLAG;


  /*  The Blue Tooth communication  functions */
bool btResponseOK();
bool btresponseVersion();
bool btresponseWait();

};

