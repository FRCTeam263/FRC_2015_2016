#include "WPILib.h"

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
		Victor *exampleVictor = new Victor(0);
		exampleVictor->Set(0.7);

		Joystick *exampleJoystick = new Joystick(0);
		double axisVar;
		bool butPressed;

		axisVar = exampleJoystick->GetRawAxis(2);
		butPressed = exampleJoystick->GetRawButton(1);

		Encoder *sampleEncoder = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
		sampleEncoder->Reset();
		int count = sampleEncoder->Get();
		double rate = sampleEncoder->GetRate();
		bool direction = sampleEncoder->GetDirection();
		bool stopped = sampleEncoder->GetStopped();



		// CleanUp
		delete exampleJoystick;
		delete exampleVictor;
		delete sampleEncoder;
	}

	void Test() {
	}
};
START_ROBOT_CLASS(Robot);
