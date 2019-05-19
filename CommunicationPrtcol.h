#include "globalConstant.h"

#include "UART.h"

enum {COMMAND_MODE=10,READ_BROADCAST,REASSIGN_MODE,AUTO_MODE};

enum {RSSI=0,DIST_2_OBST,GEAR,ROV_SPEED};
enum {SPEED=1,SET_OBST,A_M_RSSI,L_R_STR};


class Communication_lib{
  
public:
  
  unsigned char SendData[RXDATASIZE];
  unsigned char RecvdDatatemp[20];
  unsigned char RecvdData[6];
  unsigned char roverParameters[4];

  Communication_lib ();
  void ReceivedDataFunc(uartModem & DataPort);
  void  broadcastOutData(uartModem & DataPort);
  bool isRcvdDataRdy(){return packetRdy;}


private:  

  bool packetRdy;
 char DataOut[6];
 int8_t count;

Ticker TmrIntr; 

};