/*
 * AfterPID.h
 *
 *  Created on: Jan 10, 2015
 *      Author: Administrator
 */

#ifndef OMEGAX_SRC_MISC_AFTERPID_H_
#define OMEGAX_SRC_MISC_AFTERPID_H_

#include <math.h>

class AfterPID {
public:
	AfterPID(void);
	~AfterPID(void);

	float GetOutput(float current, float targetAngle, float deadband, bool zeroIInDeadband = true);
	void SetPID(float P, float I, float D, float Multiplier = 1);
	void CalcEvolPID(float InputMin, float InputMax, float OutputMin, float OutputMax, bool SetI = false);


	void ResetPID();

private:
	float kP, kI, kD;
	float I_err, Prev_P_err;
	float P_err;
	float D_err;

	float Output, PrevOutput;

	float s_Multiplier;
};

#endif /* OMEGAX_SRC_MISC_AFTERPID_H_ */
