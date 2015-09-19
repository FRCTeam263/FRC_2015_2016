#include "WPILib.h"
/*
 * here is some code for the led strip. RoboRIO is master in I2C
 */
class Robot: public SampleRobot {

public:
	//function i made to send a char. it has to be in this format:
	//unsigned char color[1] = { 'c' };
	//sendColor(color);
	void sendColor(char* theColor) {
        if (theSerialPort->Write(theColor,1)) {
		   printf("Did not work.\n");
		}
		else
		{
		   printf("Sent Command: %d\n",*theColor);
		}
	}

	SerialPort *theSerialPort;

	Robot() {
		theSerialPort = new SerialPort(9600);
		printf("Constructor Completed\n");
	}

	~Robot() {
		delete theSerialPort;
		printf("Destructor Completed\n");
	}

	void Autonomous() {

	}

	void OperatorControl() {
		printf("OperatorControl START\n");
		const int totalColors = 3;
		char colors[totalColors] = { 'r', 'g', 'b' };
		while (IsOperatorControl() && IsEnabled())
		{
			for (int i=0; i<totalColors; i++) {
			   sendColor(&colors[i]);
			   Wait(1.0);
			}
		}
		printf("OperatorControl EXIT\n");
	}

	void Test() {

	}
};

START_ROBOT_CLASS(Robot);
