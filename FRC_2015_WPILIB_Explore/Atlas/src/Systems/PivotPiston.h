/*
 * PivotPiston.h
 *
 *  Created on: Aug 5, 2015
 *      Author: James
 */

#ifndef SRC_SYSTEMS_PIVOTPISTON_H_
#define SRC_SYSTEMS_PIVOTPISTON_H_

#include "Joystick.h"
#include "../Defines.h"
#include "Utilities.h"
#include <DoubleSolenoid.h>

class PivotPiston {
public:
	PivotPiston();
	virtual ~PivotPiston();

	void CommandPivotPistonPosition(Joystick *drivePad);

	enum PivotPistonPosition { Retract, Deploy };
	void CommandPivotPistonPosition(PivotPistonPosition commandedPivotPosition);

private:
	Utilities *theUtilities;
	DoubleSolenoid *theDoubleSolenoid;
};

#endif /* SRC_SYSTEMS_PIVOTPISTON_H_ */
