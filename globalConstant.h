#include "mbed.h"
#include <string>
#ifndef GLOBALCONSTANT_H
#define GLOBALCONSTANT_H

#define TX_FLAG 0x01  //00000001
#define RX_FLAG 0x02  //00000010
#define RX_TERMINATOR '\n'  //00000010

#define RXDATASIZE 6
#define PACKET_START 77
#define PACKET_STOP  70
#define RESET 0


#define RX_LEN 30
#define TX_LEN 20
#define BT_REGISTER_SIZE 20
#define WARMUP_TIME      1     
#define AT_WAIT_TIME   19      // in 1 sec AT will responds
#define ON     true   
#define OFF    false    

#define ERROR 9595
#define SUCCESS 7575
#define OUT_OF_RANGE 165
#define RECORDS   7
#define previous(n) (RECORDS+n)
//#define COMMAND_MODE   10
#define DATA_MODE   12

enum{NO_DIRECTION, LEFT_TURN, RIGHT_TURN, AUTO, MANUAL, RSSI_READ};
enum{SET_SPEED=1,SET_OBSTACLE,L_R_STRAIGHT,AUTO_MAN_RSSI};

/*
engineDrivingParams (70 , 1);   //speed and direction ctrl
 rangerObjt(10);                // ranging time assign
 
 uint16_t ==> unsigned int 16 bit
 uint8_t ==>  unsigned char 8 bit
   
*/

#endif