#include "WPILib.h"
#include "time.h"
class Robot: public SampleRobot {
	Joystick *gamePad;
public:
	Robot() {
		gamePad = new Joystick(0);
	}
	~Robot() {
		delete gamePad;
	}
	void Autonomous() {

	}

	void OperatorControl() {

            for(int x = 0; x<200; x++)
            {
            	printf("%d\n",(int)clock());
            	Wait(0.06);
            }


	}

	void Test() {
	}
};

START_ROBOT_CLASS(Robot);
