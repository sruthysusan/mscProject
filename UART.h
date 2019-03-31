#include "mbed.h"
#include <string> 
#include "globalConstant.h"

class uartModem {
  
public: 
    


 Serial *serialPort;  // keep as public for straight connection 
typedef uint32_t BAUD;


uartModem (BAUD baudRate);
~uartModem();

void sendUartString(char* strData);  // data pointing by reference method
bool stackRxbuffer();

bool isRxdataReady();
void enableRxStatusFlag (bool enable);



private:

uint8_t statusFLAG;
uint8_t rx_MsgBuffer[RX_LEN];

};