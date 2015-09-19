#ifndef OMEGAX_SRC_SYSTEMS_AUTONOMOUS_H_
#define OMEGAX_SRC_SYSTEMS_AUTONOMOUS_H_

#include "WPILib.h"
#include "LiftSystem.h"
#include "MecanumDrive.h"
#include "ElevatorSpeedAlgorithm.h"

class AutonomousSystem{
public:
	AutonomousSystem(void);
	~AutonomousSystem(void);

	void Run3ToteAuto(MecanumDrive *drive, LiftSystem *lifter);
	void RunNothing(MecanumDrive *drive, LiftSystem *lifter);

private:
	typedef enum{Reset, Lift1Tote, Stack1Tote, Lift2Totes, Stack2Totes, Lift3Totes, DriveToAutoZone} AutoMode;

	AutoMode autoMode;
	ElevatorSpeedAlgorithm *toteLifterOutput;
	ElevatorSpeedAlgorithm *canLifterOutput;
	ElevatorSpeedAlgorithm *driveOutput;
};



#endif /* OMEGAX_SRC_SYSTEMS_AUTONOMOUS_H_ */
