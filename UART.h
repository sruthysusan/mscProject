#include "mbed.h"
#include "events/mbed_events.h"

class uartModem {
  
public: 
Serial *serialPort;  // keep as public for straight connection 
typedef uint32_t BAUD;

uartModem (BAUD baudRate);
~uartModem();
void sendUart();

void callback() ;
Thread t(osPriorityNormal);

private:
  


};