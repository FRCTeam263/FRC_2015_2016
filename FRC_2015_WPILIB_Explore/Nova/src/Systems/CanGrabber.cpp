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
	limitSwitchMaximized = new DigitalInput(8);
	limitSwitchMinimized = new DigitalInput(8);
	canExtend->Set(DoubleSolenoid::kOff);

}

CanGrabber::~CanGrabber() {
	delete grabber;
	delete canExtend; // Tejas owes someone (me) a Cookie!!!!
	delete limitSwitchMaximized;
	delete limitSwitchMinimized;

}

void CanGrabber::Extend(Joystick *gamePad) {
	if ((gamePad->GetRawButton(3)) && (limitSwitchMaximized->Get() != 1)) {
		grabber->Set(1);
	} else if ((gamePad->GetRawButton(4))
			&& (limitSwitchMinimized->Get() != 1)) {
		grabber->Set(-1);
	} else {
		grabber->Set(0);
	}

//	if ((limitSwitchMaximized->Get() == 1)
//			|| (limitSwitchMinimized->Get() == 1)) {
//		grabber->Set(0);
//	}

	if (gamePad->GetRawButton(5)) {
		canExtend->Set(DoubleSolenoid::kForward);
	} else if (gamePad->GetRawButton(6)) {
		canExtend->Set(DoubleSolenoid::kReverse);
	} else {
		canExtend->Set(DoubleSolenoid::kOff);
	}
}
