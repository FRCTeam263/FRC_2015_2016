#ifndef SHOOTER_H_
#define SHOOTER_H_

#include "Relay.h"
#include "Joystick.h"
#include "../Globals.h"
#include "../Defines.h"
#include "Utilities.h"
#include "VisionSystem.h"
#include "../Misc/DashboardConnecter.h"

class Shooter{
public:
	Shooter(void);
	~Shooter(void);

	void ShootBall(void);
	void AutonShooterForward(void);
	void AutonShooterBackward(void);
	void StopShooter(void);
	
	float counter;
private:
	Victor *ShooterMotor;
	Victor *SecondShooterMotor;
	Relay *LED;
	DigitalInput *ShooterLimitSwitch;
	AnalogChannel *ShooterPot;
	AnalogChannel *UltraSonicSensor;

	DriverStation *ds;
	Utilities *utilities;
	DashboardConnecter *dashboard;
	//VisionSystem *visionsystem;
	
	float ShooterAngle;
	bool ShooterOvershot;
	float SonicSensorValue;
};

#endif
