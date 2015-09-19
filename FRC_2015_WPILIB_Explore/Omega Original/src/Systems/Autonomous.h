/*
 * Autonomous.h
 *
 *  Created on: Jan 9, 2015
 *      Author: Administrator
 */

#ifndef SRC_SYSTEMS_AUTONOMOUS_H_
#define SRC_SYSTEMS_AUTONOMOUS_H_

#include "WPILib.h"
#include "LiftSystem.h"
#include "MecanumDrive.h"
#include "../Misc/AfterPID.h"

class AutonomousSystem{
public:
	AutonomousSystem(void);
	~AutonomousSystem(void);

	void Run3ToteAuto(MecanumDrive *drive, LiftSystem *lifter);
	void Run2ToteAuto(MecanumDrive *drive, LiftSystem *lifter);

private:
	typedef enum{Reset, Lift1Tote, Stack1Tote, Lift2Totes, Stack2Totes, Lift3Totes, DriveToAutoZone} AutoMode;

	AutoMode autoMode;
};



#endif /* SRC_SYSTEMS_AUTONOMOUS_H_ */
