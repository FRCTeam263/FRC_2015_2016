#ifndef SRC_SYSTEMS_MECANUMDRIVE_H_
#define SRC_SYSTEMS_MECANUMDRIVE_H_

#include "CANTalon.h"
#include "Gyro.h"
#include "Joystick.h"
#include "LiftSystem.h"
#include "Utilities.h"
#include "ElevatorSpeedAlgorithm.h"
#include "../Defines.h"
#include <math.h>

class MecanumDrive{
public:
	MecanumDrive(void);
	~MecanumDrive(void);

	void Drive(Joystick *drivePad);
	void TurnToAngle(Joystick *drivePad);
	void AutonDriveStraight(bool GyroEnabled = false, float Speed = 0,
							bool Strafe = false);
	void AutonTurn(float Speed = 0);
	void SetZero(void);
	int AverageEncoders(void);
	int AverageTurnRightEncoders(void);
	int AverageTurnLeftEncoders(void);
	int AverageLeftStrafe(void);
	int AverageRightStrafe(void);
	void ResetEncoders(void);

	CANTalon *FLMotor;
	CANTalon *FRMotor;
	CANTalon *BLMotor;
	CANTalon *BRMotor;

	Gyro *mecanumGyro;
	ElevatorSpeedAlgorithm *turnOutput;
private:
	Utilities *utilities;

	float FLSpeed;
	float FRSpeed;
	float BLSpeed;
	float BRSpeed;
};



#endif /* SRC_SYSTEMS_MECANUMDRIVE_H_ */
