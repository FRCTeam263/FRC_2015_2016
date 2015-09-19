#include "WPILib.h"

class Robot: public SampleRobot {

	AnalogInput *exampleInput;
	Joystick *gamePad;
public:

	Robot() {
		exampleInput = new AnalogInput(0);
		gamePad = new Joystick(0);
	}

	~Robot() {
		delete exampleInput;
		delete gamePad;
	}

	void Autonomous() {

	}

	void OperatorControl() {
		float SonicSensorValue = 0;
		printf("Before loop\n");
		while (gamePad->GetRawButton(1) != 1) {
			//sonicReturn = exampleInput->GetVoltage();
			SonicSensorValue = exampleInput->GetVoltage();
			//	const float VoltageToFeet = 512 / 5 / 12;  // Vcc of 5V divided by 512 gives inches.  Then div 12 to make feet.
			//	float SonicSensorValueInFeet = SonicSensorValue * VoltageToFeet;

			//const float SonarVoltsToFeet = 13.0 / 3.8;
			//float SonicSensorValueInFeet = SonicSensorValue * SonarVoltsToFeet;
              float SonicSensorValueInInches = SonicSensorValue*(512/5);

			printf("sonicReturn = %f,	inches = %f feet=%f	\n", SonicSensorValue,SonicSensorValueInInches, SonicSensorValueInInches/12);
			SmartDashboard::PutNumber("SonicFeet",SonicSensorValueInInches/12);
              Wait(0.2);
		}
		printf("After loop\n");
	}
	void Test() {

	}
};

START_ROBOT_CLASS(Robot);
