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
	float Acceleration(float time, bool forward);
private:
};



#endif /* SRC_SYSTEMS_UTILITIES_H_ */
