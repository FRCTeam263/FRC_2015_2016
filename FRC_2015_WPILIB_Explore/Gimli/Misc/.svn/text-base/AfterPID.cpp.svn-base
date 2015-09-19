#include "AfterPID.h"

AfterPID::AfterPID(float P, float I, float D, float Multiplier) {
	kP = P;
	kI = I;
	kD = D;
	
	s_Multiplier = Multiplier;
}

void AfterPID::SetPID(float P, float I, float D, float Multiplier) {
	kP = P;
	kI = I;
	kD = D;
	
	s_Multiplier = Multiplier;
}

float AfterPID::GetOutput(float current, float target, float deadband, bool zeroIInDeadband) {
	P_err = target - current;
	I_err += P_err;
	D_err = P_err - Prev_P_err;

	if ((Prev_P_err < 0 && P_err >= 0) || (Prev_P_err >= 0 && P_err < 0)) {
		if(zeroIInDeadband)
			I_err = 0;
	}

	Prev_P_err = P_err;

	float out;

	if (P_err >= (deadband * -1) && P_err < deadband && zeroIInDeadband) {
		out = 0;
		I_err = 0;
	} else {
		out = ((kP * P_err) + (kI * I_err) - (kD * D_err));
	}

	if (out < -1)
		out = -1;
	else if (out > 1)
		out = 1;
	else if(out == 0 && zeroIInDeadband)
		I_err = 0;
	
	out *= s_Multiplier;
	
	return out;
}

void AfterPID::ResetPID()
{
	I_err = 0;
	Prev_P_err = 0;
	P_err = 0;
	D_err = 0;
}
