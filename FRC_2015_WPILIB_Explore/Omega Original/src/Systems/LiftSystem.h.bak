#ifndef SRC_SYSTEMS_LIFTSYSTEM_H_
#define SRC_SYSTEMS_LIFTSYSTEM_H_

#include "WPILib.h"
#include "Utilities.h"
#include "../Misc/AfterPID.h"

class LiftSystem{
public:
	LiftSystem(void);
	~LiftSystem(void);

	void RunLongLift(Joystick *gamePad);
	void RunShortLift(Joystick *gamePad);
	void ResetLifter(void);
	void SetZero(void);
	void TestLifter(Joystick *gamePad);

	Victor *liftMotor;
	CANTalon *shortLiftMotor1;
	CANTalon *shortLiftMotor2;
	CANTalon *longLiftMotor1;
	VictorSP *longLiftMotor2;

	Talon *leftWheel;
	Talon *rightWheel;

	DigitalInput *shortBottomLS;
	DigitalInput *longBottomLS;
	DigitalInput *shortTopLS;
	DigitalInput *longTopLS;
	DigitalInput *toteTouchSensor;

	AfterPID *shortPID;
	AfterPID *longPID;
private:
	Utilities *utilities;

	float shortEncoderDistance;
	float longEncoderDistance;

};

#endif /* SRC_SYSTEMS_LIFTSYSTEM_H_ */
