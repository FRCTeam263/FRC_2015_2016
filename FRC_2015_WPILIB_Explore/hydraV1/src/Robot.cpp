#include "WPILib.h"
#include <time.h>

#define Button_A_1 1
/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public SampleRobot {

public:
	Robot() {
	}

	void Autonomous() {
	}

	void OperatorControl() {
		//TODO PUT NEW CODE HERE!!!
		DigitalInput *limitSwitch = new DigitalInput(1);
		while (true){
			printf("Switch Value: %d\n", limitSwitch->Get());
			Wait(1);
		}

		delete limitSwitch;
	}

	void Test() {
	}

};
START_ROBOT_CLASS(Robot);
