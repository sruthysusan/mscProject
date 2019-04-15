#include "globalConstant.h"

enum MODE_OPER{COMMAND_MODE=0,READ_BROADCAST,REASSIGN_MODE,AUTO_MODE};


struct packVitals {
uint8_t m_Address;
uint8_t m_modeOper;
uint8_t m_data[7];
uint8_t m_endBytes[2];
};