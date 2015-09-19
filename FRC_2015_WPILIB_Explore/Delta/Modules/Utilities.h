#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "WPILib.h"
#include "../Defines.h"
#include <math.h>

class Utilities{
private:
	
public:
	Utilities(void);
	~Utilities(void);
	//void lowPassFilterLoop(unsigned int *input, unsigned int *output, unsigned int len, double fs, double fc);
	static double lowPassFilterRealtime(double input, double previous, double fs, double fc);
	static double deadbandValue(double input, double threshold);
	static double boundValue(double input, double min, double max);
};
#endif
