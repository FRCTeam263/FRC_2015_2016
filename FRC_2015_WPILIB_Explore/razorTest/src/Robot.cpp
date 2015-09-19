#include "WPILib.h"
class Robot: public SampleRobot {
	Joystick *razorPad;
public:
	Robot() {
		razorPad = new Joystick(0);
	}
	~Robot() {
		delete razorPad;

	}

	void Autonomous() {

	}

	void OperatorControl() {
		while (IsOperatorControl() && IsEnabled()) {
			for (int x = 1; x <= 16; x++) {
				if (razorPad->GetRawButton(x)) {
					printf("Button %d Was Pressed\n", x);

				}
			}
			Wait(0.09);
		}
	}

	void Test() {

	}
};

START_ROBOT_CLASS(Robot);
