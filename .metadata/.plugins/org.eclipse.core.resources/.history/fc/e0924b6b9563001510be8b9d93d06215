#include "WPILib.h"
#include "Utilities.h"

#include <Solenoid.h>
#include <DoubleSolenoid.h>

#define DOUBLESOLENOID_LEFT_CANNON_FORWARD_CHANNEL 0
#define DOUBLESOLENOID_LEFT_CANNON_REVERSE_CHANNEL 1

#define DOUBLESOLENOID_RIGHT_CANNON_FORWARD_CHANNEL 2
#define DOUBLESOLENOID_RIGHT_CANNON_REVERSE_CHANNEL 3

#define GAMEPAD_BUTTON_A 1
#define GAMEPAD_BUTTON_B 2
#define GAMEPAD_BUTTON_X 3
#define GAMEPAD_BUTTON_Y 4
#define GAMEPAD_LEFT_BUMPER 5
#define GAMEPAD_RIGHT_BUMBER 6
#define GAMEPAD_BUTTON_LEFT 7
#define GAMEPAD_BUTTON_RIGHT 8

#define GAMEPAD_AXIS_LEFT_STICK_HORIZONTAL 0
#define GAMEPAD_AXIS_LEFT_STICK_VERTICAL 1
#define GAMEPAD_AXIS_LEFT_TRIGGER 2
#define GAMEPAD_AXIS_RIGHT_TRIGGER 3
#define GAMEPAD_AXIS_RIGHT_STICK_HORIZONTAL 4
#define GAMEPAD_AXIS_RIGHTT_STICK_VERTICAL 5


class Robot: public SampleRobot
{
	RobotDrive myRobot; // robot drive system
	Joystick *gamepad;
	Timer HeartbeatTimer;
	const double HeartbeatTickDurationInSeconds = 5.0;
	long lifetimeTickCounter = 0;
	Utilities *theUtilities;
	DoubleSolenoid *theDoubleSolenoid_LeftCannon;
	DoubleSolenoid *theDoubleSolenoid_RightCannon;

public:
	Robot() :
			myRobot(0, 1, 2, 3)	// these must be initialized in the same order
	{
		myRobot.SetExpiration(0.1);
		HeartbeatTimer.Reset();
		HeartbeatTimer.Start();
		printf("RoboRIO Initialized.\n");
		theUtilities = new Utilities();
		gamepad = new Joystick(0);
		theDoubleSolenoid_LeftCannon = new DoubleSolenoid(DOUBLESOLENOID_LEFT_CANNON_FORWARD_CHANNEL,DOUBLESOLENOID_LEFT_CANNON_REVERSE_CHANNEL);
		theDoubleSolenoid_LeftCannon->Set(DoubleSolenoid::kReverse);
		theDoubleSolenoid_RightCannon = new DoubleSolenoid(DOUBLESOLENOID_RIGHT_CANNON_FORWARD_CHANNEL,DOUBLESOLENOID_RIGHT_CANNON_REVERSE_CHANNEL);
		theDoubleSolenoid_RightCannon->Set(DoubleSolenoid::kReverse);
	}

	~Robot()
	{
		theDoubleSolenoid_LeftCannon->Set(DoubleSolenoid::kReverse);
		theDoubleSolenoid_RightCannon->Set(DoubleSolenoid::kReverse);
		delete theDoubleSolenoid_LeftCannon;
		delete theDoubleSolenoid_RightCannon;
		delete theUtilities;
		delete gamepad;
	}

	void Autonomous()
	{
		myRobot.SetSafetyEnabled(false);
		while(IsAutonomous() && IsEnabled())
		{
			ProcessHeartbeat();

			//myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
			Wait(0.005); 				//    for 2 seconds
			//myRobot.Drive(0.0, 0.0); 	// stop robot
		}
	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl()
	{

		myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled())
		{
			//CommandPivotPistonPosition();
			ProcessFireControl();
			ProcessHeartbeat();

			myRobot.ArcadeDrive(gamepad); // drive with arcade style (use right stick)
			Wait(0.005);				// wait for a motor update time
		}
	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}

private:

	void ProcessHeartbeat()
    {
		if (HeartbeatTimer.HasPeriodPassed(HeartbeatTickDurationInSeconds))
		{
			printf("Heartbeat tick %ld (every %f seconds).\n",
					lifetimeTickCounter++,
					HeartbeatTickDurationInSeconds);
			HeartbeatTimer.Reset();
			HeartbeatTimer.Start();
		}
    }

//	int TogglePiston()
//	{
//		if (theDoubleSolenoid->Get() == DoubleSolenoid::kReverse) {
//    		theDoubleSolenoid->Set(DoubleSolenoid::kForward); // Deploy it so its anchored, and robot can pivot arround it.
//    	} else {
//    		theDoubleSolenoid->Set(DoubleSolenoid::kReverse); // Retract it so robot can move around.
//    	}
//		return theDoubleSolenoid->Get();
//
//	}
//
//	void CommandPivotPistonPosition() {
//	    if (theUtilities->GetJoystickButton(GAMEPAD_BUTTON_A, gamepad)) {
//	    	if (theDoubleSolenoid->Get() == DoubleSolenoid::kReverse) {
//	    		theDoubleSolenoid->Set(DoubleSolenoid::kForward); // Deploy it so its anchored, and robot can pivot arround it.
//	    	} else {
//	    		theDoubleSolenoid->Set(DoubleSolenoid::kReverse); // Retract it so robot can move around.
//	    	}
//			printf("PistonPositionToggled (%d)\n", TogglePiston());
//	    }
//	}

	void ProcessFireControl() {
		static bool lastArmingButtonState = 0;
		if (gamepad->GetRawButton(GAMEPAD_BUTTON_Y)) {
			gamepad->SetRumble(Joystick::kLeftRumble,0.7);
			if (!lastArmingButtonState) {
				printf("DANGER!  Shooter is Armed.  DANGER!\n");
			}
			lastArmingButtonState = true;
			if (gamepad->GetRawAxis(GAMEPAD_AXIS_LEFT_TRIGGER) > 0.8) {
				printf("LEFT CANNON FIRED!\n");
				theDoubleSolenoid_LeftCannon->Set(DoubleSolenoid::kForward);
				Wait(0.1);
				theDoubleSolenoid_LeftCannon->Set(DoubleSolenoid::kReverse);
			}
			if (gamepad->GetRawAxis(GAMEPAD_AXIS_RIGHT_TRIGGER) > 0.8) {
				printf("RIGHT CANNON FIRED!\n");
				theDoubleSolenoid_RightCannon->Set(DoubleSolenoid::kForward);
				Wait(0.1);
				theDoubleSolenoid_RightCannon->Set(DoubleSolenoid::kReverse);
			}
		} else {
			gamepad->SetRumble(Joystick::kLeftRumble,0.0);
			if (lastArmingButtonState) {
				printf("Shooter is DISARMED.\n");
			}
			lastArmingButtonState = false;
		}
	}
};

START_ROBOT_CLASS(Robot);
