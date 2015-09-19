#ifndef MECHANUMDRIVE_H_
#define MECHANUMDRIVE_H_

#include "WPILib.h"
#include"../Defines.h"
#include "../Misc/AfterPID.h"
#include "Utilities.h"
#include <math.h>

class MechanumDrive {
public:
	
	MechanumDrive(void);
	~MechanumDrive(void);
	
	void Drive();
	void SetupDrive();
	
	void AutonDrive();
	
	/*void RunGyro();
	void RunGyroDigital(void *owner);
	void StartNotifier();
	void StopNotifier();
	*/
private:
	
	Victor *frontLeftMotor;
	Victor *frontRightMotor;
	Victor *backLeftMotor;
	Victor *backRightMotor;
	
	Utilities *utilities;
	
	/*Encoder *frontLeftEncoder;
	Encoder *frontRightEncoder;
	Encoder *backLeftEncoder;
	Encoder *backRightEncoder;*/
	
	Gyro *gyroSensor;
	
	//Notifier *gyroNotifier;
	
	float frontLeftSpeed, frontRightSpeed, backLeftSpeed, backRightSpeed;
	//float currentAngle;
	//float angle;
	//double filteredAngle;
	
	void Equalize();
	
	void MechanumCalculations(float x, float y, float rotation);
};

#endif
