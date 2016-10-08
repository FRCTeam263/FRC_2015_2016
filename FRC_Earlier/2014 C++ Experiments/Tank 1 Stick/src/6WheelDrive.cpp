#include "6WheelDrive.h"
#include <cmath>

SixWD::SixWD(){
	LeftSide = new Talon(1);//The 0 and 1 are where the PWM wire is connected to your motor controller
	LeftSide2 = new Talon(3);
	RightSide = new Talon(2);//on the roboRIO. So here it is controlling 2 talons in PWM slots 0 and 1 on the roboRIO.
	RightSide2 = new Talon(0);

	LeftSide->Set(0);
	RightSide->Set(0);
}

SixWD::~SixWD(){
	delete LeftSide;
	delete RightSide;
}

void SixWD::Drive(Joystick *drivePad){
	float LeftSpeed = drivePad->GetRawAxis(4);
	float RightSpeed = drivePad->GetRawAxis(5) * -1; //This is assuming you have a
	//logitech controller with 2 analog sticks, one stick for each side.

	if(fabs(LeftSpeed) < 0.05){
		LeftSpeed = 0;
	}
	if(fabs(RightSpeed) <0.05){//sets deadband values so you have to move the
		RightSpeed = 0;// analog stick to a value higher than 0.2/-0.2 for the robot to move.
	}


		printf("Left Stick: %f, Right Stick: %f \n", LeftSpeed,RightSpeed);

	LeftSide->Set(LeftSpeed);
	LeftSide2->Set(LeftSpeed);
	RightSide->Set(RightSpeed);
	RightSide2->Set(RightSpeed);
}
