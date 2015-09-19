#include "WPILib.h"
/*
 * here is some code for the led strip. RoboRIO is master in I2C
 */
class Robot: public SampleRobot {

	I2C *i2c;

public:

	Robot() {
		i2c = new I2C(I2C::kOnboard, 1);
		printf("Constructor Completed\n");
	}

	~Robot() {
		delete i2c;
		printf("Destructor Completed\n");
	}

	void Autonomous() {

	}

	void OperatorControl() {
		printf("OperatorControl START\n");
		const int totalColors = 3;
		unsigned char colors[totalColors] = { 'r', 'g', 'b' };
		while (IsOperatorControl() && IsEnabled())
		{
			for (int i=0; i<totalColors; i++) {
			   sendColor(colors[i]);
			   Wait(1.0);
			}
		}
		printf("OperatorControl EXIT\n");
	}

	void Test() {

	}

//	void sendColor(unsigned char theColor) {
//		printf("Sent Command: %d\n",theColor);
//		printf("return: %d\n",i2c->Transaction(&theColor, 1, NULL, 0));
//
//	}

	void sendColor(unsigned char theColor) {
		// Three alternate calls each works.  Transaction, WriteBulk or Write.
		// But the Transaction's return value is always true, and Write always sends an extra character (2 instead of 1).
		// So for single character transmit communication, it appears WriteBulk works best.
//		  if (i2c->Transaction(&theColor, 1, NULL, 0)) {  // Works but always returns true.
//        if (i2c->Write(0,theColor)) {  // Write always sends an extra character, can't get it to stop.  Use WriteBulk or Transaction instead.
        if (i2c->WriteBulk(&theColor,1)) {
		   printf("Did not work.\n");
			//if i2c->Transaction returns true, it doesn't work
			//i2c->Transaction returns false, it works
		}
		else
		{
		   printf("Sent Command: %d\n",theColor);
		}
	}


};

START_ROBOT_CLASS(Robot);
