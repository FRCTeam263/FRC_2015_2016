#include "liftsystem.h"

liftmotor::liftmotor(void) {
	Liftmotor1 = new Victor(0);
}
liftmotor::~liftmotor(void) {
	delete Liftmotor1;
}
#define Axis_LeftStick_Vertical 1
void liftmotor::LiftTote(Joystick *GameController) {
	printf("Entered liftmotor::LiftTote");

	float currentSpeed = 0.0;
	float LeftStickVerticalDir = 0;
	float slope_stick2Motor = (1);
	LeftStickVerticalDir = GameController->GetRawAxis(Axis_LeftStick_Vertical);
	printf("Axis(%d) = %f\n", Axis_LeftStick_Vertical ,LeftStickVerticalDir);
	currentSpeed = slope_stick2Motor * LeftStickVerticalDir;
	Liftmotor1->Set(currentSpeed);




	/*
 	static float currentSpeed = 0;
    const float motorSpeedStepping = 0.25;

	if(  GameController->GetRawButton(2) == 1)
	{
		currentSpeed += motorSpeedStepping;
		if (currentSpeed>1.0)currentSpeed = 1.0;
	}
	if(  GameController->GetRawButton(1) == 1)
	{
		currentSpeed -= motorSpeedStepping;
		if (currentSpeed< (-1.0))currentSpeed = -1.0;

	}
	Liftmotor1->Set(currentSpeed);  // I used I as the power level
	//Wait(.2);
*/



	/*
	for (float i = 0.0; i <= 1.0; i = i + 0.02) {
		printf("iteration number: %f\n", i);
		Liftmotor1->Set(i);  // I used I as the power level
		Wait(.2);
	}
	for (float i = 1.0; i >= 0.0; i = i - 0.02) {
			printf("iteration number: %f\n", i);
			Liftmotor1->Set(i);  // I used I as the power level
			Wait(.2);
		}
	Wait(1);
	for (float i = 0.0; i >= -1.0; i = i - 0.02) {
				printf("iteration number: %f\n", i);
				Liftmotor1->Set(i);  // I used I as the power level
				Wait(.2);
			}
	for (float i = -1.0; i <= 0.0; i = i + 0.02) {
				printf("iteration number: %f\n", i);
				Liftmotor1->Set(i);  // I used I as the power level
				Wait(.2);
			}
	/*
	 Liftmotor1->Set(0);
	 Wait(6);
	 Liftmotor1->Set(0.1);
	 Wait(6);
	 Liftmotor1->Set(0.2);
	 Wait(6);
	 Liftmotor1->Set(0.3);
	 Wait(6);
	 Liftmotor1->Set(0.4);
	 Wait(6);
	 Liftmotor1->Set(0.5);
	 Wait(6);
	 Liftmotor1->Set(0.6);
	 Wait(6);
	 Liftmotor1->Set(0.7);
	 Wait(6);
	 Liftmotor1->Set(0.8);
	 Wait(6);
	 Liftmotor1->Set(0.9);
	 Wait(6);
	 Liftmotor1->Set(1);

	 */

	printf("Exiting liftmotor::LiftTote");

}
