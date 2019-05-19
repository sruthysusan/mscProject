
#include "CommunicationPrtcol.h"


Communication_lib ::Communication_lib ()
{
  SendData[0]=PACKET_START;  SendData[RXDATASIZE-1]=PACKET_STOP;
  packetRdy =false;
  //TmrIntr.attach(&ReceivedData, 1);
}



void Communication_lib :: broadcastOutData(uartModem & DataPort)
{
 //  memcpy(SendData,roverParameters,sizeof(roverParameters));
   
   DataOut[0]=PACKET_START;  DataOut[RXDATASIZE-1]=PACKET_STOP;
   for(int i=0;i<4;i++)
      DataOut[i+1]=roverParameters[i];
   DataPort.sendUartData(DataOut);
}


void Communication_lib :: ReceivedData(uartModem & DataPort) 
{
  static uint8_t count;
  
  packetRdy=false;
  if(count >= RXDATASIZE)
  {
    count = RESET;
   if( SendData[0] == PACKET_START && SendData[RXDATASIZE-1] == PACKET_STOP)
   {
     packetRdy=true;
   }
  }
  else
  {
    SendData[count++] = DataPort.serialPort->getc();
  
  }
}
