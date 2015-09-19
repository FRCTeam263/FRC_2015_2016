#include "WPILib.h"
#include "Systems/MecanumDrive.h"
#include "Systems/LiftSystem.h"
#include "Systems/Autonomous.h"
#include "Systems/PivotPiston.h"

class Atlas: public SampleRobot
{
public:
	Joystick *drivePad;
	Joystick *gamePad;

	MecanumDrive *drive;
	LiftSystem *lifter;
	PivotPiston *pivotPiston;

	AutonomousSystem *auton;

	DigitalInput *auto2tote1Can;
	DigitalInput *auto1Tote1Can;
	DigitalInput *auto3ToteStack;
	DigitalInput *autoDriveFwd;
	DigitalInput *autoFastCan;
	Timer *timer;

	Atlas()
	{
		drivePad = new Joystick(0);
		gamePad = new Joystick(1);

		drive = new MecanumDrive();
		lifter = new LiftSystem();
		pivotPiston = new PivotPiston();

		auton = new AutonomousSystem();
		autoFastCan = new DigitalInput(5);
		autoDriveFwd = new DigitalInput(6);
		auto3ToteStack = new DigitalInput(7);
		auto1Tote1Can = new DigitalInput(8);
		auto2tote1Can = new DigitalInput(9);
		timer = new Timer;


	}

	~Atlas(){
		delete drivePad;
		delete gamePad;
		delete drive;
		delete lifter;
		delete pivotPiston;
		delete auton;
	}

	void Autonomous()
	{
		//float tiltAngleRad = drive->NavX->GetPitch() * (M_PIl/180);
		while(IsAutonomous() && IsEnabled()){
			drive->CalibrateNavX();
			//if(drive->NavX->GetPitch() < 25 && drive->NavX->GetPitch() > -25){
				if(auto2tote1Can->Get() == 0){//DIO 9
					auton->Run2Tote1CanAuto(drive, lifter, pivotPiston);
				}
				else if(auto1Tote1Can->Get() == 0){//DIO 8
					auton->Run1Tote1CanAuto(drive, lifter, pivotPiston);
				}
				else if(auto3ToteStack->Get() == 0){//DIO 7
					auton->Run3Tote1CanAuto(drive, lifter, pivotPiston);
				}
				else if(autoDriveFwd->Get() == 0){//DIO 6
					auton->RunDriveForward(drive);
				}
				else if(autoFastCan->Get() == 0){//DIO 5
					auton->RunFast1Can(drive, lifter);
				}
				else{//Not Plugged In
					auton->RunNothing(drive, lifter);
				}
			/*}
			else if(drive->NavX->GetPitch() > 25){
				drive->AutonDriveStraight(false, tiltAngleRad);
			}
			else if(drive->NavX->GetPitch() < -25){
				drive->AutonDriveStraight(false, tiltAngleRad);
			}
			else{
				auton->RunNothing(drive, lifter);
			}*/
			//printf("Angle: %f\n", drive->NavX->GetYaw());
		}
	}

	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			drive->CalibrateNavX();
			drive->Drive(drivePad);
			lifter->RunLifter(gamePad, drivePad);
			//printf("StrafeLeft: %d\n", drive->AverageLeftStrafe());
			//printf("Tote: %f\n", lifter->shortLiftMotor1->Get());
			//printf("Angle: %f\n", drive->mecanumGyro->GetAngle());
			//printf("FL: %f\t FR: %f \t BL: %f\t BR: %f\t Avg: %d\n", drive->FLMotor->GetPosition(), drive->FRMotor->GetPosition(), drive->BLMotor->GetPosition(), drive->BRMotor->GetPosition(), drive->AverageLeftStrafe());
			//printf("WideEncoder: %f\t ShortEncoder: %f\n", lifter->canLiftMotor->GetPosition(), lifter->shortLiftMotor1->GetPosition());
			pivotPiston->CommandPivotPistonPosition(drivePad);
		}
	}
};

START_ROBOT_CLASS(Atlas);
