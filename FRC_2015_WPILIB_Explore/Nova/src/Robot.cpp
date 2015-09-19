#include "WPILib.h"
#include "Systems/MecanumDrive.h"
#include "Systems/LiftSystem.h"
#include "Systems/CanGrabber.h"
#include "Systems/Autonomous.h"

class Robot: public SampleRobot
{
	Joystick *drivePad;
	Joystick *gamePad;
	Joystick *autonMode;

	MecanumDrive *drive;
	LiftSystem *lifter;
	CanGrabber *grabber;

	AutonomousSystem *auton;
public:

	Robot()
	{
		drivePad = new Joystick(0);
		gamePad = new Joystick(1);
		autonMode = new Joystick(2);

		drive = new MecanumDrive();
		lifter = new LiftSystem();
		grabber = new CanGrabber();

		auton = new AutonomousSystem();
	}

	~Robot(){
		delete drivePad;
		delete gamePad;
		delete autonMode;
		delete drive;
		delete lifter;
		delete grabber;
		delete auton;
	}

	void Autonomous()
	{
		/*while(IsAutonomous() && IsEnabled()){

			if(autonMode->GetRawButton(1)){
				auton->Run3ToteAuto(drive, lifter);
			}


			else if(autonMode->GetRawButton(2)){

			}
		}

		while(IsOperatorControl() && IsDisabled()){
			lifter->ResetLifter();
			drive->SetZero();
		}*/
	}

	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			drive->Drive(drivePad);
			//lifter->TestLifter(drivePad);
			//lifter->RunShortLift(gamePad);
			//lifter->RunLongLift(drivePad);
			grabber->Extend(drivePad);
		}

		/*while(IsOperatorControl() && IsDisabled()){
			lifter->ResetLifter();
			drive->SetZero();
		}*/
	}
};

START_ROBOT_CLASS(Robot);



/*Pokemon Battle 2015
 *
 * A wild Mercado appeared.
 * Trainer Bryan sent out Chris.
 * Go Chris!
 * Mercado used splash.
 * It does nothing.
 * Chris used RKO.
 * It's super effective.
 * Mercado fainted.
 * Chris gains 1337 EXP.
 *
 *
 *
 * A while later....
 * Trainer Josh challenges Trainer Bryan.
 * "I'm Asian!" - Trainer Josh
 * Trainer Josh sent out Raj.
 * Trainer Bryan sent out Mr. Wentzel
 * Raj used CAD
 * It failed.
 * Mr. Wentzel used Long Speech
 * Raj fell asleep.
 * Trainer Josh recalls Raj.
 * Come back Raj!
 * Trainer Josh sent out Mercado.
 * Go show them your worth Mercado!
 * Mr. Wentzel used Salad.
 * Mercado is poisoned.
 * Mercado is hurt by the poison.
 * Mercado used Eat Bread.
 * He is no longer effected by poison and gains full HP.
 * Mr. Wentzel used Extensive Knowledge of Aeronautical Engineering.
 * It's a Critical Hit!
 * Mercado fainted.
 * Trainer Josh sent out Mateo.
 * Show them dis dik Mateo!
 * Trainer Bryan recalls Mr. Wentzel.
 * Come back Mr. Wentzel!
 * Trainer Bryan sent out Chris.
 * Mateo used
 */
