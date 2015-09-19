/*
 * PivotPiston.cpp
 *
 *  Created on: Aug 5, 2015
 *      Author: James
 */

#include "PivotPiston.h"
#include "Utilities.h"

PivotPiston::PivotPiston() {
	theUtilities = new Utilities();
	theDoubleSolenoid = new DoubleSolenoid(PIVOT_PISTON_FORWARD_CHANNEL,PIVOT_PISTON_REVERSE_CHANNEL);
	theDoubleSolenoid->Set(DoubleSolenoid::kReverse);  // Retract it so robot can move around.
}

PivotPiston::~PivotPiston() {
	theDoubleSolenoid->Set(DoubleSolenoid::kReverse); // Retract it so robot can move and be moved around.

	delete theUtilities;
	delete theDoubleSolenoid;
}

void PivotPiston::CommandPivotPistonPosition(Joystick *drivePad) {
    if (theUtilities->GetJoystickButton(2, drivePad)) {
    	if (theDoubleSolenoid->Get() == DoubleSolenoid::kReverse) {
    		theDoubleSolenoid->Set(DoubleSolenoid::kForward); // Deploy it so its anchored, and robot can pivot arround it.
    	} else {
    		theDoubleSolenoid->Set(DoubleSolenoid::kReverse); // Retract it so robot can move around.
    	}
    }
}

void PivotPiston::CommandPivotPistonPosition(PivotPistonPosition commandedPivotPosition) {
    if (PivotPiston::Deploy == commandedPivotPosition) {
		theDoubleSolenoid->Set(DoubleSolenoid::kForward); // Deploy it so its anchored, and robot can pivot arround it.
	} else {
		theDoubleSolenoid->Set(DoubleSolenoid::kReverse); // Retract it so robot can move around.
	}
}

