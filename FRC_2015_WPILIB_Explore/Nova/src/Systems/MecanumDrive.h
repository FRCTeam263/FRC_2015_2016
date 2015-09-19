#ifndef SRC_SYSTEMS_MECANUMDRIVE_H_
#define SRC_SYSTEMS_MECANUMDRIVE_H_

#include "WPILib.h"
#include "LiftSystem.h"
#include "Utilities.h"
#include <math.h>

class MecanumDrive{
public:
	MecanumDrive(void);
	~MecanumDrive(void);

	void Drive(Joystick *drivePad);
	void AutonDriveStraight(bool GyroEnabled, float Speed);
	void AutonTurn(float Speed);
	void SetZero(void);

	CANTalon *FLMotor;
	CANTalon *FRMotor;
	CANTalon *BLMotor;
	CANTalon *BRMotor;

	Encoder *FLWheel;
	/*Encoder *BLWheel;
	Encoder *FRWheel;
	Encoder *BRWheel;*/

private:
	Utilities *utilities;

	Gyro *mecanumGyro;

	float FLSpeed;
	float FRSpeed;
	float BLSpeed;
	float BRSpeed;
};



#endif /* SRC_SYSTEMS_MECANUMDRIVE_H_ */
