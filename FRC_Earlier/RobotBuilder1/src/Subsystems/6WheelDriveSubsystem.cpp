// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.




#include "6WheelDriveSubsystem.h"
#include "../RobotMap.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

6WheelDriveSubsystem::6WheelDriveSubsystem() : Subsystem("6WheelDriveSubsystem") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	cANJaguar1 = RobotMap::6WheelDriveSubsystemCANJaguar1;
	cANJaguar2 = RobotMap::6WheelDriveSubsystemCANJaguar2;
	cANJaguar3 = RobotMap::6WheelDriveSubsystemCANJaguar3;
	cANJaguar4 = RobotMap::6WheelDriveSubsystemCANJaguar4;
	robotDrive41 = RobotMap::6WheelDriveSubsystemRobotDrive41;
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void 6WheelDriveSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

