
#include "CommunicationPrtcol.h"


Communication_lib ::Communication_lib ()
{
  SendData[0]=PACKET_START;  SendData[RXDATASIZE-1]=PACKET_STOP;

  //TmrIntr.attach(&ReceivedData, 1);
}


void Communication_lib ::ReceivedData() 
{
  

}