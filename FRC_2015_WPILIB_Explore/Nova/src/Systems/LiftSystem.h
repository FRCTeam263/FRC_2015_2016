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

	Victor *liftMotor; // Used for prototypes
	CANTalon *shortLiftMotor1;
	CANTalon *shortLiftMotor2;
	CANTalon *longLiftMotor1;
	VictorSP *longLiftMotor2;

	Talon *leftWheel; // not used delete this
	Talon *rightWheel; // not used delete this


	DigitalInput *shortBottomLiftSystem;
	DigitalInput *longBottomLiftSystem;
	DigitalInput *shortTopLiftSystem;
	DigitalInput *longTopLS;
	DigitalInput *shortToteTouchSensor;
	DigitalInput *longToteTouchSensor;


	AfterPID *shortPID;
	AfterPID *longPID;
private:
	Utilities *utilities;

	float shortEncoderDistance;
	float longEncoderDistance;

};

#endif /* SRC_SYSTEMS_LIFTSYSTEM_H_ */
