#include "WPILib.h"

#include <DoubleSolenoid.h>
#define PIVOT_PISTON_FORWARD_CHANNEL 0
#define PIVOT_PISTON_REVERSE_CHANNEL 1


/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public SampleRobot
{
	RobotDrive myRobot; // robot drive system
	Joystick stick; // only joystick
	Timer HeartbeatTimer;
	const double HeartbeatTickDurationInSeconds = 5.0;
	long lifetimeTickCounter = 0;
	DoubleSolenoid *theDoubleSolenoid;

public:
	Robot() :
			myRobot(0, 1, 2, 3),	// these must be initialized in the same order
			stick(0)		// as they are declared above.
	{
		myRobot.SetExpiration(0.1);
		HeartbeatTimer.Reset();
		HeartbeatTimer.Start();
		printf("RoboRIO Initialized.\n");
		theDoubleSolenoid = new DoubleSolenoid(PIVOT_PISTON_FORWARD_CHANNEL,PIVOT_PISTON_REVERSE_CHANNEL);
		theDoubleSolenoid->Set(DoubleSolenoid::kReverse);  // Retract it so robot can move around.
	}

	~Robot()
	{
		theDoubleSolenoid->Set(DoubleSolenoid::kReverse); // Retract it so robot can move and be moved around.
		delete theDoubleSolenoid;
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
		myRobot.SetSafetyEnabled(false);
		while(IsAutonomous() && IsEnabled())
		{
			ProcessHeartbeat();

			//myRobot.Drive(-0.5, 0.0); 	// drive forwards half speed
			Wait(1.0); 				//    for 2 seconds
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
			ProcessHeartbeat();

			myRobot.ArcadeDrive(stick); // drive with arcade style (use right stick)
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
			printf("Heartbeat tick %ld (every %f seconds).  DoubleSolenoid position(%d)\n",
					lifetimeTickCounter++,
					HeartbeatTickDurationInSeconds,
					TogglePiston());
			HeartbeatTimer.Reset();
			HeartbeatTimer.Start();
		}
    }

	int TogglePiston()
	{
		if (theDoubleSolenoid->Get() == DoubleSolenoid::kReverse) {
    		theDoubleSolenoid->Set(DoubleSolenoid::kForward); // Deploy it so its anchored, and robot can pivot arround it.
    	} else {
    		theDoubleSolenoid->Set(DoubleSolenoid::kReverse); // Retract it so robot can move around.
    	}
		return theDoubleSolenoid->Get();

	}

};

START_ROBOT_CLASS(Robot);
