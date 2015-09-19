#include "WPILib.h"

class Robot: public SampleRobot
{
	DigitalOutput DualSonicSensorTrigger;
	AnalogInput SonicSensor1;
	AnalogInput SonicSensor2;
	Timer SonicTimer;
public:
	Robot()
	{
		*DualSonicSensorTrigger = new DigitalOutput(0);
		*SonicSensor1 = new AnalogInput(0);
		*SonicSensor2 = new AnalogInput(1);
	}

	~Robot()
	{
		delete DualSonicSensorTrigger;
		delete SonicSensor1;
		delete SonicSensor2;
	}

	void Autonomous()
	{

	}

	void OperatorControl()
	{

		while (IsOperatorControl() && IsEnabled())
		{

			Wait(0.005);				// wait for a motor update time
		}
	}

	void Test()
	{
	}

	void TriggerTheDualSonicSensor()
	{
	  // Pulse the trigger to kick off continuous mode of sonic sensors cascaded.
      DualSonicSensorTrigger.Set(0);
	  Wait(10); // milliseconds
      DualSonicSensorTrigger.Set(1);
      Wait(10); // milliseconds
      DualSonicSensorTrigger.Set(0);
      Wait(10); // milliseconds

      SonicTimer.Reset();
	}

	bool GetDualSonicSensorRanges()

};

START_ROBOT_CLASS(Robot);
