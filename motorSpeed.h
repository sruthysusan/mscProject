#include "globalConstant.h"


#define NEUTRAL    0
#define FIRSTGEAR  25
#define SECONDGEAR 50
#define THIRDGEAR  75
#define FOURTHGEAR 100

enum DirectionGear {FORWARD,REVERSE};  


class motorSetting
{
  
private:
  typedef uint8_t SPEEDGEAR;
  float currentGear;
//  PwmOut* Speedester; 
  PwmOut  A1Apin,A1Bpin,B1Apin ,B1Bpin;
//  PwmOut A1Apin(PTC1),A1Bpin(PTC2),B1Apin(PTB3),B1Bpin(PTB2);
  
  
public:
  
  motorSetting(SPEEDGEAR startSpeed);
  
  void engineDrivingParams(uint16_t gear, bool forwardMotion);   // determines the speed of motor rotation and Direction of rotation
  
};