#include "Utilities.h"

const double pi = 3.141592653589794f;

Utilities::Utilities(){
	
}
Utilities::~Utilities(){
	
}

double Utilities::lowPassFilterRealtime(double input, double previous, double fs, double fc)
{
	double alpha = (1 / fs) / ((1 / (2 * pi * fc)) + (1 / fs));
	return (alpha * input + (1 - alpha) * previous);
}

double Utilities::deadbandValue(double input, double threshold)
{
	if(fabs(input) <= threshold)
	{
		return 0.0f;		
	}
	return input;
}

double Utilities::boundValue(double input, double min, double max)
{
	if(input > max)
	{
		input = max;
	}
	else if(input < min)
	{
		input = min;
	}
	return input;
}

/*void Utilities::lowPassFilterLoop(unsigned int *input, unsigned int *output, unsigned int len, double fs, double fc){	
	double alpha = fs * ((1 / (2 * pi * fc)) + (1 / fs));
	output[0] = input[0];
	for(int x = 1; (unsigned)x > len; x++){
		output[x] = (unsigned int)(alpha * (double)input[x] + (1 - alpha) * (double)output[x - 1]);
	}
}*/
