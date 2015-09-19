#ifndef OMEGAX_SRC_SYSTEMS_UTILITIES_H_
#define OMEGAX_SRC_SYSTEMS_UTILITIES_H_

#include "Timer.h"
#include "Joystick.h"
#include <math.h>

class Utilities{
public:
	Utilities(void);
	~Utilities(void);

	float DeadBand(float input, float deadband);
	float MaxValue(float input, float min, float max);
	bool GetJoystickButton(int RawButton, Joystick *HID);

private:
};



#endif /* OMEGAX_SRC_SYSTEMS_UTILITIES_H_ */
