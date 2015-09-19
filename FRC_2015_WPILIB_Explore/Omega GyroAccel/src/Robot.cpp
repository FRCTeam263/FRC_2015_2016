#include "WPILib.h"
#include "Systems/MecanumDrive.h"
#include "Systems/LiftSystem.h"
#include "Systems/Autonomous.h"

class Omega: public SampleRobot
{
public:
	Joystick *drivePad;
	Joystick *gamePad;
	Joystick *autonMode;

	MecanumDrive *drive;
	LiftSystem *lifter;

	AutonomousSystem *auton;

	Omega()
	{
		drivePad = new Joystick(0);
		gamePad = new Joystick(1);
		autonMode = new Joystick(2);

		drive = new MecanumDrive();
		lifter = new LiftSystem();

		auton = new AutonomousSystem();

		/*CameraServer::GetInstance()->SetQuality(50);
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");*/
	}

	~Omega(){
		delete drivePad;
		delete gamePad;
		delete autonMode;
		delete drive;
		delete lifter;
		delete auton;
	}

	void Autonomous()
	{
		while(IsAutonomous() && IsEnabled()){
			//drive->AutonDriveStraight(false, 0.5);
			auton->Run3ToteAuto(drive, lifter);
		}
	}

	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			drive->Drive(drivePad);
			lifter->RunLifter(gamePad);
			printf("FL: %f\t FR: %f \t BL: %f\t BR: %f\n", drive->FLMotor->GetPosition(), drive->FRMotor->GetPosition(), drive->BLMotor->GetPosition(), drive->BRMotor->GetPosition());
			//printf("WideEncoder: %f\t ShortEncoder: %f\n", lifter->canLiftMotor->GetPosition(), lifter->shortLiftMotor1->GetPosition());
		}
	}
};

START_ROBOT_CLASS(Omega);
