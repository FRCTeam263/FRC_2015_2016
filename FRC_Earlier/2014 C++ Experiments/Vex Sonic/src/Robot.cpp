#include "WPILib.h"

class Robot: public SampleRobot {

	DigitalOutput *vexSonicTrigger;
	DigitalInput *vexSonicEchoDetector;
	Ultrasonic *sonicSensor;

	Timer vexSonicTimer;

public:
	Robot() {
		vexSonicTrigger = new DigitalOutput(8);		// labeled input on vex
		vexSonicEchoDetector = new DigitalInput(9);	// labeled output on vex
		sonicSensor = new Ultrasonic(vexSonicTrigger, vexSonicEchoDetector);

		sonicSensor->SetAutomaticMode(true);
	}

	~Robot() {
		delete vexSonicTrigger;
		delete vexSonicEchoDetector;
		delete sonicSensor;
	}

	void Autonomous() {
	}

	void OperatorControl() {
		while (IsEnabled() && IsOperatorControl()) {
			printf("%f\n", sonicSensor->GetRangeInches()/12);
		}
	}

	void Test() {

	}

};

START_ROBOT_CLASS(Robot);
