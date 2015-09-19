#include "WPILib.h"
#include "ElevatorSpeedAlgorithm.h"
#include <time.h>


const int numberOfElevatorLevels = 7;
const int elevatorLevels[numberOfElevatorLevels] =
	{ 0, 800, 1000, 1800, 2000,	2800, 3000 };

class Robot: public SampleRobot {
	Joystick *myJoystick = new Joystick(234);
	Encoder *myEncoder = new Encoder(0, 1, false, Encoder::EncodingType::k4X);
	Victor *myMotor = new Victor(0);
	ElevatorSpeedAlgorithm myElevatorSpeedAlgorithm;

	int currentElevatorLevel = 0;

	// This routine creates blackout periods for each joystick button
	// to ensure quick repeated calls do not result in taking the same
	// action multiple times.  The users press and release of a joystick
	// button probably lasts much longer than the OperatorControl loop iteration.
	bool getJoystickButton(int buttonIndex)
	{
		static bool firstTimeCalled = true;
		const clock_t DelayBeforeRecognizeNextPress = 2 * CLOCKS_PER_SEC;
		const int maxButtons = 20;
		static clock_t ButtonTimeLastPressed[maxButtons];
		bool currentPressedState = false;

		if (firstTimeCalled)
		{
			// Make sure all buttons blackout periods are expired.
			firstTimeCalled = false;
			clock_t firstTimestamp = clock() - DelayBeforeRecognizeNextPress;
			for (int i = 0; i < maxButtons; i++)
			{
				ButtonTimeLastPressed[i] = firstTimestamp;
			}
		}
		else
		{
			// Only allow caller to see the actual button state when its respective
			// blackout period has expired.  Allow user to see this only once, and reset the
			// blackout timer.
			if ((clock() - ButtonTimeLastPressed[buttonIndex]) > DelayBeforeRecognizeNextPress)
			{
				currentPressedState = myJoystick->GetRawButton(buttonIndex);
				ButtonTimeLastPressed[buttonIndex] = clock();
				printf("Button[%d] Pressed.\n",buttonIndex);
			}
			else
			{
				currentPressedState = false;
			}
		}
		return currentPressedState;
	}

public:
	Robot() {
	}

	~Robot() {
		delete myJoystick;
		delete myEncoder;
		delete myMotor;
	}

	void Autonomous() {
	}

	void OperatorControl() {

		while (IsOperatorControl() && IsEnabled()) {

			while (!getJoystickButton(0)) {
				if (getJoystickButton(1)) {
					if (++currentElevatorLevel > numberOfElevatorLevels)
						currentElevatorLevel = numberOfElevatorLevels;
				}
				else if (getJoystickButton(2)) {
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

	void Test() {
	}

};

START_ROBOT_CLASS(Robot);
