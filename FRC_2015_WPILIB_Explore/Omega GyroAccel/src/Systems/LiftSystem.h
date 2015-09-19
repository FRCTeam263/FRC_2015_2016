#ifndef OMEGAX_SRC_SYSTEMS_LIFTSYSTEM_H_
#define OMEGAX_SRC_SYSTEMS_LIFTSYSTEM_H_

#include "CANTalon.h"
#include "Joystick.h"
#include "DigitalInput.h"
#include "Utilities.h"
#include "ElevatorSpeedAlgorithm.h"
#include "../Defines.h"

class LiftSystem{
public:
	LiftSystem(void);
	~LiftSystem(void);

	void RunLifter(Joystick *gamePad);
	void RunLongLift(Joystick *gamePad);
	void RunShortLift(Joystick *gamePad);
	void ResetLifter(void);
	void SetZero(void);
	void TestLifter(Joystick *gamePad);
	void SetCanSpeed(float Speed = 0);
	void SetToteSpeed(float Speed = 0);

	CANTalon *shortLiftMotor1;
	CANTalon *shortLiftMotor2;
	CANTalon *canLiftMotor;

	DigitalInput *shortBottomLS;
	DigitalInput *canBottomLS;
	DigitalInput *shortTopLS;
	DigitalInput *canTopLS;
	DigitalInput *toteTouchSensor;
	DigitalInput *canTouchSensor;

private:
	Utilities *utilities;
	ElevatorSpeedAlgorithm *toteLifterOutput;
	ElevatorSpeedAlgorithm *canLifterOutput;

	float toteEncoderDistance;
	float canEncoderDistance;
};

#endif /* OMEGAX_SRC_SYSTEMS_LIFTSYSTEM_H_ */
