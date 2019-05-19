
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


void Communication_lib :: ReceivedDataFunc(uartModem & DataPort) 
{
    
  packetRdy=false;
  if(count >18) count=0;
  
   RecvdDatatemp[count++] = DataPort.serialPort->getc();
  
  if( RecvdDatatemp[count-1] == PACKET_STOP)
  {
  
   memmove(RecvdData, RecvdDatatemp + (count-RXDATASIZE) * sizeof(unsigned char), RXDATASIZE * sizeof(unsigned char));
     count=0;
   if( RecvdDatatemp[0] == PACKET_START )
   {
     packetRdy=true;
   }
  }
  
  
}
