//2015 Robot Code
//Created by Tejas Prasad
//Assisted by Mr. Tripi & the Programming Dungeon
#include "WPILib.h"
#include "Systems/MecanumDrive.h"
#include "Systems/LiftSystem.h"
#include "Systems/Autonomous.h"

class Atlas: public SampleRobot
{
public:
	Joystick *drivePad;
	Joystick *gamePad;

	MecanumDrive *drive;
	LiftSystem *lifter;

	AutonomousSystem *auton;

	Atlas()
	{
		drivePad = new Joystick(0);
		gamePad = new Joystick(1);

		drive = new MecanumDrive();
		lifter = new LiftSystem();

		auton = new AutonomousSystem();
	}

	~Atlas(){
		delete drivePad;
		delete gamePad;
		delete drive;
		delete lifter;
		delete auton;
	}

	void Autonomous()
	{
		drive->mecanumGyro->Reset();
		while(IsAutonomous() && IsEnabled()){
			//auton->Run2Tote1CanAuto(drive, lifter);
			//auton->Run1Tote1CanAuto(drive, lifter);
			//auton->Run1CanPickup(drive, lifter);
			//auton->RunDriveForward(drive);
			//printf("Angle: %f\n", drive->mecanumGyro->GetAngle());
		}
	}

	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			drive->Drive(drivePad);
			lifter->RunLifter(gamePad, drivePad);
			//printf("Tote: %f\n", lifter->shortLiftMotor1->Get());
			//printf("Angle: %f\n", drive->mecanumGyro->GetAngle());
			//printf("FL: %f\t FR: %f \t BL: %f\t BR: %f\t Avg: %d\n", drive->FLMotor->GetPosition(), drive->FRMotor->GetPosition(), drive->BLMotor->GetPosition(), drive->BRMotor->GetPosition(), drive->AverageLeftStrafe());
			//printf("WideEncoder: %f\t ShortEncoder: %f\n", lifter->canLiftMotor->GetPosition(), lifter->shortLiftMotor1->GetPosition());
		}
	}
};

START_ROBOT_CLASS(Atlas);
