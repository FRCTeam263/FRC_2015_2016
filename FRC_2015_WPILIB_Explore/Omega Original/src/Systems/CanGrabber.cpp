/*
 * CanGrabber.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: Administrator
 */

#include <Systems/CanGrabber.h>

CanGrabber::CanGrabber() {
	grabber = new Victor(0);
	canExtend = new DoubleSolenoid(0, 1);

	canExtend->Set(DoubleSolenoid::kOff);

}

CanGrabber::~CanGrabber() {
	delete grabber;
}

void CanGrabber::Extend(Joystick *gamePad){
	if(gamePad->GetRawButton(3)){
		grabber->Set(1);
	}
	else if(gamePad->GetRawButton(4)){
		grabber->Set(-1);
	}
	else{
		grabber->Set(0);
	}

	if(gamePad->GetRawButton(5)){
		canExtend->Set(DoubleSolenoid::kForward);
	}
	else if(gamePad->GetRawButton(6)){
		canExtend->Set(DoubleSolenoid::kReverse);
	}
	else{
		canExtend->Set(DoubleSolenoid::kOff);
	}
}
