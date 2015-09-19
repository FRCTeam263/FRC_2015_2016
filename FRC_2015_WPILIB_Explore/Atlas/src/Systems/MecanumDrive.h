#ifndef SRC_SYSTEMS_MECANUMDRIVE_H_
#define SRC_SYSTEMS_MECANUMDRIVE_H_

#include "CANTalon.h"
#include "Gyro.h"
#include "Joystick.h"
#include "LiftSystem.h"
#include "Utilities.h"
#include "ElevatorSpeedAlgorithm.h"
#include "../NavXLib/AHRS.h"
#include "../NavXLib/AHRSProtocol.h"
#include "../NavXLib/IMU.h"
#include "../NavXLib/IMUAdvanced.h"
#include "../NavXLib/IMUProtocol.h"
#include "../NavXLib/IMURegisters.h"
#include "../Defines.h"
#include <math.h>

class MecanumDrive{
public:
	MecanumDrive(void);
	~MecanumDrive(void);

	void Drive(Joystick *drivePad);
	void CalibrateNavX(void);
	void AutonDriveStraight(bool GyroEnabled = false, float Speed = 0,
							bool Strafe = false);
	void AutonTurn(float Speed = 0);
	void AutonDiagonalStrafe(bool NegativeX = true, float Speed = 0);
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

	IMU *NavX;
	ElevatorSpeedAlgorithm *turnOutput;
private:
	Utilities *utilities;
	SerialPort *serialPort;
	bool FirstRun;

	float FLSpeed;
	float FRSpeed;
	float BLSpeed;
	float BRSpeed;
};



#endif /* SRC_SYSTEMS_MECANUMDRIVE_H_ */
