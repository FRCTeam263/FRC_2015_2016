#include "PneumaticCannons.h"

extern Joystick *twistStick;


PneumaticCannons::PneumaticCannons(){
	leftCannon = new Solenoid(LEFT_CANNON);
	rightCannon = new Solenoid(RIGHT_CANNON);
	
	leftCannon->Set(false);
	rightCannon->Set(false);
}
PneumaticCannons::~PneumaticCannons(){
	
}
void PneumaticCannons::setOuput(){
	
	leftCannon->Set(false);
	rightCannon->Set(false);
	
	if(twistStick->GetRawButton(3) && twistStick->GetRawButton(1)){
		leftCannon->Set(true);
	}
	if(twistStick->GetRawButton(2) && twistStick->GetRawButton(1)){
		rightCannon->Set(true);
	}
}
