//2014 Robot Code
//Manual Hammer Control
#include "WPILib.h"
#include "Globals.h"
#include "Defines.h"
#include "Modules/MecanumDrive.h"
#include "Modules/Shooter.h"
#include "Modules/BallPickup.h"
#include "Modules/VisionSystem.h"

Joystick *drivePad;
Joystick *gamePad;

MecanumDrive *driveTrain;
BallPickup *pickupBall;
Shooter *ballShooter;
//VisionSystem *vision;

Timer *autonTimer;

class Robot2014 : public SimpleRobot
{ 
public:
	Robot2014(void){
		GetWatchdog().SetExpiration(1);
		GetWatchdog().SetEnabled(false);
		
		drivePad = new Joystick(DRIVEPAD);
		gamePad = new Joystick(GAMEPAD);
		
		driveTrain = new MecanumDrive();
		ballShooter = new Shooter();
		pickupBall = new BallPickup();
		//vision = new VisionSystem();
		
		autonTimer = new Timer();
	}

	void Autonomous(void)
	{
		autonTimer->Reset();
		autonTimer->Start();
		while(IsAutonomous())
		{
			GetWatchdog().SetEnabled(false);
			if(autonTimer->Get() < 2){
				pickupBall->AutonPickup();
			}
			else if(autonTimer->Get() > 2 && autonTimer->Get() < 4){//time is 1.5s forward for 1point auton
				pickupBall->AutonBallEject();
			}
			else if(autonTimer->Get() > 4 && autonTimer->Get() < 6){
				driveTrain->AutonDrive(true, false);
			}
			else if(autonTimer->Get() > 7 && autonTimer->Get() < 7.25){
				driveTrain->StopDrive();
				ballShooter->AutonShooterBackward();
			}
			else if(autonTimer->Get() > 7.3 && autonTimer->Get() < 8){
				ballShooter->AutonShooterForward();
			}
			/*if(autonTimer->Get() < 1.5){
				driveTrain->AutonDrive(true, false);
			}*/
			/*if(autonTimer->Get() < 1){
				driveTrain->AutonDrive(true, false);
			}*/
			else{
				driveTrain->StopDrive();
				pickupBall->StopPickup();
				ballShooter->StopShooter();
			}
		}
		autonTimer->Stop();
	}

	void OperatorControl(void)
	{
		while (IsOperatorControl())
		{
			driveTrain->Drive();
			pickupBall->Pickup();
			ballShooter->ShootBall();
		}
	}
};

START_ROBOT_CLASS(Robot2014);
