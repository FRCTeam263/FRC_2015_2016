#ifndef SRC_SYSTEMS_UTILITIES_H_
#define SRC_SYSTEMS_UTILITIES_H_

#include "WPILib.h"
#include <math.h>

class Utilities{
public:
	Utilities(void);
	~Utilities(void);

	float DeadBand(float input, float deadband);
	float MaxValue(float input, float min, float max);
	bool GetJoystickButton(int RawButton, Joystick *HID);
	void LimitSwitchRumble(Joystick *HID, DigitalInput *LS, float RumbleLength = 2, bool HardRumble = true);
private:
};



#endif /* SRC_SYSTEMS_UTILITIES_H_ */
