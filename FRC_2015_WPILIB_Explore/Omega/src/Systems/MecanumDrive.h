#ifndef OMEGAX_SRC_SYSTEMS_MECANUMDRIVE_H_
#define OMEGAX_SRC_SYSTEMS_MECANUMDRIVE_H_

#include "WPILib.h"
#include "CANTalon.h"
#include "Gyro.h"
#include "Joystick.h"
#include "LiftSystem.h"
#include "Utilities.h"
#include "../Defines.h"
#include <math.h>

class MecanumDrive{
public:
	MecanumDrive(void);
	~MecanumDrive(void);

	void Drive(Joystick *drivePad);
	void AutonDriveStraight(bool GyroEnabled = false,
							float Speed = 0,
							bool Strafe = false);
	void AutonTurn(float Speed = 0);
	void SetZero(void);
	void ResetEncoders(void);
	CANTalon *FLMotor;
	CANTalon *FRMotor;
	CANTalon *BLMotor;
	CANTalon *BRMotor;

private:
	Utilities *utilities;

	Gyro *mecanumGyro;
	BuiltInAccelerometer *builtInAccel;

	float FLSpeed;
	float FRSpeed;
	float BLSpeed;
	float BRSpeed;

	double SnapshotOfGyroValue;
	double SnapshotOfAccelerometerValueX;
	double SnapshotOfAccelerometerValueY;
	double SnapshotOfAccelerometerValueZ;

	void SnapshotAutonGyroAndAccelerometerValues(void);
};



#endif /* OMEGAX_SRC_SYSTEMS_MECANUMDRIVE_H_ */
