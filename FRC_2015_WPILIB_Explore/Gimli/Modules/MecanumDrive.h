#ifndef MECANUM_DRIVE_H_
#define MECANUM_DRIVE_H_

#include "Gyro.h"
#include "Victor.h"
#include "Joystick.h"
#include "../Defines.h"
#include "Utilities.h"
#include <math.h>

class MecanumDrive{
public:
	MecanumDrive(void);
	~MecanumDrive(void);
	
	void Drive(void);
	void SetUpDrive(void);
	void MecanumGyroDrive(float x, float y, float rotation);
	void AutonDrive(bool GyroEnabled, bool Forward);
	void AutonTurn(bool TurnLeft);
	void StopDrive(void);
	
	Gyro *RobotAngle;
	
private:
	Victor *FrontLeftMotor;
	Victor *FrontRightMotor;
	Victor *BackLeftMotor;
	Victor *BackRightMotor;
	
	Utilities *utilities;

	float frontLeftSpeed;
	float frontRightSpeed;
	float backLeftSpeed;
	float backRightSpeed;
};

#endif
