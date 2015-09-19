#include "WPILib.h"

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
	Joystick stick; // only joystick
	DigitalOutput dOut;
	bool currentLedState;

public:
	Robot() :
			stick(0),		// as they are declared above.
			dOut(0)
	{
		currentLedState = 0;
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
		dOut.Set(uint32_t(currentLedState = !currentLedState));
		Wait(2.0); 				//    for 2 seconds
		dOut.Set(uint32_t(currentLedState = !currentLedState));
		Wait(2.0); 				//    for 2 seconds
	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			Wait(2.0);				// wait for a motor update time
			dOut.Set(uint32_t(currentLedState = !currentLedState));
		}
	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot);
