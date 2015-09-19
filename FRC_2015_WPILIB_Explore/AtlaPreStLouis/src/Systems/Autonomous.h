#ifndef SRC_SYSTEMS_AUTONOMOUS_H_
#define SRC_SYSTEMS_AUTONOMOUS_H_

#include "WPILib.h"
#include "LiftSystem.h"
#include "MecanumDrive.h"
#include "ElevatorSpeedAlgorithm.h"

class AutonomousSystem{
public:
	AutonomousSystem(void);
	~AutonomousSystem(void);

	void Run3Tote1CanAuto(MecanumDrive *drive, LiftSystem *lifter);
	void Run1Tote2CanAuto(MecanumDrive *drive, LiftSystem *lifter);
	void Run2Tote1CanAuto(MecanumDrive *drive, LiftSystem *lifter);
	void Run1Tote1CanAuto(MecanumDrive *drive, LiftSystem *lifter);
	void RunDriveForward(MecanumDrive *drive);
	void Run1CanPickup(MecanumDrive *drive, LiftSystem *lifter);
	void RunFast1Can(MecanumDrive *drive, LiftSystem *lifter);
	void RunNothing(MecanumDrive *drive, LiftSystem *lifter);

	ElevatorSpeedAlgorithm *turnOutput;

private:
	typedef enum{LiftCan, Lift1Tote, Rotate1Tote, StrafeRight, Drop1Tote, Lineup2Totes, DriveTo3Totes, RotateToAutoZone,
		DriveToAutoZone, RotateInAutoZone} AutoMode;

	AutoMode autoMode;
	ElevatorSpeedAlgorithm *toteLifterOutput;
	ElevatorSpeedAlgorithm *canLifterOutput;
	ElevatorSpeedAlgorithm *driveOutput;
	Timer *timer;

};



#endif /* SRC_SYSTEMS_AUTONOMOUS_H_ */
