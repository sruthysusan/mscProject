#include "globalConstant.h"

#define RXDATASIZE 6
#define PACKET_START 77
#define PACKET_STOP  70
#define RESET 0

//enum {COMMAND_MODE=0,READ_BROADCAST};//,REASSIGN_MODE,AUTO_MODE};

enum {COMMAND_MODE=10,READ_BROADCAST,REASSIGN_MODE,AUTO_MODE};

enum {RSSI=1,DIST_2_OBST,GEAR,ROV_SPEED};
enum {SPEED=1,SET_OBST,A_M_RSSI,L_R_STR};
enum{NO_DIRECTION, LEFT_TURN, RIGHT_TURN, AUTO, MANUAL, RSSI_READ};

class Communication_lib{
  
public:
  
  unsigned char SendData[RXDATASIZE];
  unsigned char RecvdData[RXDATASIZE];

Communication_lib ();
void ReceivedData();


private:  
  


Ticker TmrIntr; 

};