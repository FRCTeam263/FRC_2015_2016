#ifndef SRC_SYSTEMS_LIFTSYSTEM_H_
#define SRC_SYSTEMS_LIFTSYSTEM_H_

#include "CANTalon.h"
#include "Timer.h"
#include "Joystick.h"
#include "DigitalInput.h"
#include "Utilities.h"
#include "ElevatorSpeedAlgorithm.h"
#include "../Defines.h"

class LiftSystem{
public:
	LiftSystem(void);
	~LiftSystem(void);

	void RunLifter(Joystick *gamePad, Joystick *drivePad);
	void ResetLifter(void);
	void SetZero(void);
	void TestLifter(Joystick *gamePad);
	void SetCanSpeed(float Speed = 0);
	void SetToteSpeed(float Speed = 0);

	CANTalon *toteLiftMotor1;
	CANTalon *toteLiftMotor2;
	CANTalon *canLiftMotor;

	DigitalInput *toteBottomLS;
	DigitalInput *toteTopLS;
	DigitalInput *canBottomLS;
	DigitalInput *canTopLS;

private:
	Utilities *utilities;
	ElevatorSpeedAlgorithm *toteLifterOutput;
	ElevatorSpeedAlgorithm *canLifterOutput;

	float toteEncoderDistance;
	float canEncoderDistance;
};

#endif /* SRC_SYSTEMS_LIFTSYSTEM_H_ */
