#include "WPILib.h"
#include "CANTalon.h"

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
	CANTalon *myCANTalon;
	float CANTalonSpeed;

public:
	Robot() :
			stick(0)		// as they are declared above.
	{
		myCANTalon = new CANTalon(0 );  // Change this # to match talon iD AS PROGRAMMED
		myCANTalon->SetFeedbackDevice(CANTalon::QuadEncoder);
		myCANTalon->Set(0);
		myCANTalon->SetPosition(0);
		myCANTalon->SetSensorDirection(true);
		CANTalonSpeed = 0;
	}

	~Robot()
	{
		myCANTalon->Set(0);
		Wait(1.0);
		delete myCANTalon;
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous()
	{
	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			for (float i = 0.0; i<=1.0; i+=0.05){
				printf("Speed: %f\n", i);
				myCANTalon->Set(i);
				Wait(0.1);
				if (!(IsOperatorControl() && IsEnabled())) break;
			}
			for (float i = 1.0; i>=0.0; i-=0.05){
				printf("Speed: %f\n", i);
				myCANTalon->Set(i);
				Wait(0.1);
				if (!(IsOperatorControl() && IsEnabled())) break;
			}
		}
		myCANTalon->Set(0);
		printf("Speed: %f\n", 0.0);
	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot);
