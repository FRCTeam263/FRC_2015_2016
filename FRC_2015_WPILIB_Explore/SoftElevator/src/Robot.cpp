#include "WPILib.h"
#include "ElevatorSpeedAlgorithm.h"

const int numberOfElevatorLevels = 7;
const int elevatorLevels[numberOfElevatorLevels] = { 0, 800, 1000, 1800, 2000,
		2800, 3000 };

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
class Robot: public SampleRobot {
	Joystick *myJoystick = new Joystick(234);
	Encoder *myEncoder = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
	Victor *myMotor = new Victor(0);
	ElevatorSpeedAlgorithm myElevatorSpeedAlgorithm;

	int currentElevatorLevel = 0;

public:
	Robot() {
	}

	~Robot() {
		delete myJoystick;
		delete myEncoder;
		delete myMotor;
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous() {
	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl() {
		while (IsOperatorControl() && IsEnabled()) {
			while (!myJoystick->GetRawButton(0)) {
				if (myJoystick->GetRawButton(1)) {
					if (++currentElevatorLevel > numberOfElevatorLevels)
						currentElevatorLevel = numberOfElevatorLevels;
				}

				if (myJoystick->GetRawButton(2)) {
					if (--currentElevatorLevel < 0)
						currentElevatorLevel = 0;
				}

				myMotor->Set(
						myElevatorSpeedAlgorithm.ComputeNextMotorSpeedCommand(
								myEncoder->Get(),
								elevatorLevels[currentElevatorLevel]));

			}
		}
	}

	/**
	 * Runs during test mode
	 */
	void Test() {
	}

};

START_ROBOT_CLASS(Robot);
