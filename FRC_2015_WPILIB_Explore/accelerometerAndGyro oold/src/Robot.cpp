#include "WPILib.h"
#include "BuiltInAccelerometer.h"
#include "Gyro.h"

class Robot: public SampleRobot {

	BuiltInAccelerometer *builtInAccel;
	Gyro *gyro;
	Joystick *gamePad;

public:
	Robot() {
		gyro = new Gyro(1);
		builtInAccel = new BuiltInAccelerometer();
		gamePad = new Joystick(0);

		gyro->SetSensitivity(.007);
		gyro->Reset();
	}
	~Robot() {
		delete gyro;
		delete builtInAccel;
		delete gamePad;
	}

	void Autonomous() {

	}
	void OperatorControl() {
		while (IsOperatorControl() && IsEnabled()) {
			float gyroAngle = gyro->GetAngle();
			printf("%f\n", gyroAngle);
			//printf("The Angle Of The Gyro Is: %f\n", gyroAngle);
			Wait(0.25);

			if(gamePad->GetRawButton(1))
			{
				gyro->Reset();
			}

		}
	}

	void Test() {
	}
};

START_ROBOT_CLASS(Robot);
