#ifndef AFTERPID_H_
#define AFTERPID_H_

#include "WPILib.h"

class AfterPID {
private:
	float kP, kI, kD;
	float I_err, Prev_P_err;
	float P_err;
	float D_err;
	
	float s_Multiplier;
public:
	AfterPID(float P, float I, float D, float Multiplier = 1);
		
	float GetOutput(float current, float targetAngle, float deadband, bool zeroIInDeadband = true);
	void SetPID(float P, float I, float D, float Multiplier);
	
	void ResetPID();
};

#endif
