#include "globalConstant.h"


#define NEUTRAL 0
#define SPEED_1 1
#define SPEED_2 2
#define SPEED_3 3
#define REVERSE_SPEED 10


enum DirectionGear {FORWARD,REVERSE};  


class motorSetting
{
  
private:
  typedef uint8_t SPEEDGEAR;
  PwmOut  *A1Apin,*A1Bpin,*B1Apin ,*B1Bpin;  
  
public:
  float currentGear;
  bool  currentDirection; 
  motorSetting(SPEEDGEAR startSpeed);
  
  void engineDrivingParams(uint16_t gear, bool forwardMotion =FORWARD, uint8_t steerWheel = NO_DIRECTION);   // determines the speed of motor rotation and Direction of rotation
  
};