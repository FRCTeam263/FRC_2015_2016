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
	Timer LightingEffectsTimer;
	const double LightingDurationInSeconds = 1.0;
	Utilities *theUtilities;
	DoubleSolenoid *theDoubleSolenoid_LeftCannon;
	DoubleSolenoid *theDoubleSolenoid_RightCannon;
	I2C *i2c;

public:
	Robot() :
			myRobot(0, 1, 2, 3)	// these must be initialized in the same order
	{
		myRobot.SetExpiration(0.1);
		HeartbeatTimer.Reset();
		HeartbeatTimer.Start();
		LightingEffectsTimer.Reset();
		LightingEffectsTimer.Start();
		printf("RoboRIO Initialized.\n");
		theUtilities = new Utilities();
		gamepad = new Joystick(0);
		theDoubleSolenoid_LeftCannon = new DoubleSolenoid(DOUBLESOLENOID_LEFT_CANNON_FORWARD_CHANNEL,DOUBLESOLENOID_LEFT_CANNON_REVERSE_CHANNEL);
		theDoubleSolenoid_LeftCannon->Set(DoubleSolenoid::kReverse);
		theDoubleSolenoid_RightCannon = new DoubleSolenoid(DOUBLESOLENOID_RIGHT_CANNON_FORWARD_CHANNEL,DOUBLESOLENOID_RIGHT_CANNON_REVERSE_CHANNEL);
		theDoubleSolenoid_RightCannon->Set(DoubleSolenoid::kReverse);
		i2c = new I2C(I2C::kOnboard, 1);
	}

	~Robot()
	{
		theDoubleSolenoid_LeftCannon->Set(DoubleSolenoid::kReverse);
		theDoubleSolenoid_RightCannon->Set(DoubleSolenoid::kReverse);
		delete theDoubleSolenoid_LeftCannon;
		delete theDoubleSolenoid_RightCannon;
		delete theUtilities;
		delete gamepad;
		delete i2c;
	}

	void Autonomous()
	{
		sendColor('b');
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
			sendColor('r');
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
			ProcessLightingEffects();
			gamepad->SetRumble(Joystick::kLeftRumble,0.0);
			if (lastArmingButtonState) {
				printf("Shooter is DISARMED.\n");
			}
			lastArmingButtonState = false;
		}
	}

	void ProcessLightingEffects()
	{
		const int totalColors = 2;
		unsigned char colors[totalColors] = { 'g', 'b' };
		static int theColorCommandIndex = 0;

		if (HeartbeatTimer.HasPeriodPassed(LightingDurationInSeconds))
		{
			theColorCommandIndex = theColorCommandIndex % totalColors;
			sendColor(colors[theColorCommandIndex++]);
		}
	}

	void sendColor(unsigned char theColor) {
		// Three alternate calls each works.  Transaction, WriteBulk or Write.
		// But the Transaction's return value is always true, and Write always sends an extra character (2 instead of 1).
		// So for single character transmit communication, it appears WriteBulk works best.
//		  if (i2c->Transaction(&theColor, 1, NULL, 0)) {  // Works but always returns true.
//        if (i2c->Write(0,theColor)) {  // Write always sends an extra character, can't get it to stop.  Use WriteBulk or Transaction instead.
        if (i2c->WriteBulk(&theColor,1)) {
		   printf("Did not work.\n");
			//if i2c->Transaction returns true, it doesn't work
			//i2c->Transaction returns false, it works
		}
		else
		{
		   printf("Sent Command: %d\n",theColor);
		}
	}

};

START_ROBOT_CLASS(Robot);
