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
    printf("PivotPiston initialized to <%d>.\n",theDoubleSolenoid->Get());
}

PivotPiston::~PivotPiston() {
	theDoubleSolenoid->Set(DoubleSolenoid::kReverse); // Retract it so robot can move and be moved around.

	delete theUtilities;
	delete theDoubleSolenoid;
}

void PivotPiston::CommandPivotPistonPosition(Joystick *drivePad) {
    printf("Joystick commands PivotPiston from <%d> to ",theDoubleSolenoid->Get());
	if (theUtilities->GetJoystickButton(2, drivePad)) {
    	if (theDoubleSolenoid->Get() == DoubleSolenoid::kReverse) {
    		theDoubleSolenoid->Set(DoubleSolenoid::kForward); // Deploy it so its anchored, and robot can pivot arround it.
    	} else {
    		theDoubleSolenoid->Set(DoubleSolenoid::kReverse); // Retract it so robot can move around.
    	}
    }
    printf("<%d>.\n",theDoubleSolenoid->Get());
}

void PivotPiston::CommandPivotPistonPosition(PivotPistonPosition commandedPivotPosition) {
    printf("Program commands PivotPiston from <%d> to ",theDoubleSolenoid->Get());
    if (PivotPiston::Deploy == commandedPivotPosition) {
		theDoubleSolenoid->Set(DoubleSolenoid::kForward); // Deploy it so its anchored, and robot can pivot arround it.
	} else {
		theDoubleSolenoid->Set(DoubleSolenoid::kReverse); // Retract it so robot can move around.
	}
    printf("<%d>.\n",theDoubleSolenoid->Get());
}

