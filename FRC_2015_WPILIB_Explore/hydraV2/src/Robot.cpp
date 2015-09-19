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
	Timer *autonTimer;
public:
	Robot() {
		autonTimer = new Timer();
	}
	~Robot() {
		delete autonTimer;
	}
	void Autonomous() {
	}

	void OperatorControl() {

		//TODO PUT NEW CODE HERE!!!

		Relay *exampleRelay = new Relay(1);

		exampleRelay->Set(Relay::kOn);
		exampleRelay->Set(Relay::kForward);
		Wait(5);

		exampleRelay->Set(Relay::kReverse);
		Wait(5);
		exampleRelay->Set(Relay::kOff);
		Wait(5);

		delete exampleRelay;
		printf("Done Relay! \n");

		printf("You have 10 Seconds to press the Limit Switch!!!! \n");
		const int maxSecs = 10;
		int i = maxSecs;
		DigitalInput *limitSwitch = new DigitalInput(8);
		bool buttonPressed = false;
		autonTimer->Reset();
		autonTimer->Start();
		while ((autonTimer->Get() < maxSecs) && (!buttonPressed)){
			printf("%d \t",i--);
			printf("Switch Value: %d\n", buttonPressed = limitSwitch->Get());
			Wait(1);
		}

		delete limitSwitch;
		printf("Done OperatorControl! \n");
	}

	void Test() {
	}

};
START_ROBOT_CLASS(Robot);
