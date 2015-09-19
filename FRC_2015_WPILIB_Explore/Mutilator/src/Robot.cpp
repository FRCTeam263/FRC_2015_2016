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
		/* The assignment is: when enabled and operator control is set
		 * Then, have your motor set to 20% speed and run to an encoder count of 2000
		 * and then stop the motor.
		 * And then wait until the one button is pressed on the joystick
		 * which will set the motor to full speed     */

		printf("Entering OperatorControl :) \n");
		Victor *exampleVictor = new Victor(0);
		Joystick *exampleJoystick = new Joystick(0);
		Encoder *exampleEncoder = new Encoder(0, 1, false,
				Encoder::EncodingType::k4X);
		bool buttonPressed;
		int count;

		exampleEncoder->Reset();
		exampleVictor->Set(.2);
		while ((count = exampleEncoder->Get()) < 2000) {
			Wait(0.1);
			printf("Encoder Count: %d\n", count);
		}
		exampleVictor->Set(0.0);

		printf("Reached Target Encoder Count \n");
		/*
		 while(true){
		 Wait(0.1);
		 printf("Button Value = %d\n",exampleJoystick->GetRawButton(1));
		 }
		 */
		printf("Waiting for Button1 Press \n");
		while (exampleJoystick->GetRawButton(1) == 0) {
			Wait(0.1);

		}
		exampleVictor->Set(-1.0);

		printf("Button 1 has been pressed \n");
		clock_t t = clock();
		printf("clock = %d\n",t);
		clock_t t1 = clock();
		printf(" %d %d %d %d\n",t,t1,(clock() - t),(1.5 * CLOCKS_PER_SEC));
		while (((count =clock()) - t) < (1.5 * CLOCKS_PER_SEC)) {
			printf("Encoder Count: %d \t(%d/%d)\n", exampleEncoder->Get(), count, count-t);
			Wait(.5);

		}
		printf("Timer Elapsed \n");
		delete exampleJoystick;
		delete exampleVictor;
		delete exampleEncoder;

		/*
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
		 */
	}

	void Test() {
	}

};
START_ROBOT_CLASS(Robot);
