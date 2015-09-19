#include "WPILib.h"
#include "liftsystem.h"

liftmotor *lifter;

Victor *motor1;

class Robot: public SampleRobot
{

public:
	Robot()
	{
		lifter = new liftmotor;
		motor1 = new Victor(0);
	}

	void Autonomous()
	{
	}
	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			//lifter->LiftTote();
			motor1->Set(1);
		}
	}

};

START_ROBOT_CLASS(Robot);
