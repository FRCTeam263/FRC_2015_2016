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
	USBCamera *pCamera0;
	CameraServer *m_CameraServer;

public:
	Robot()
	{
		pCamera0 = new USBCamera("cam0",true);
		//pCamera0->pCamera0->StartCapture();

		m_CameraServer = CameraServer::GetInstance();
		m_CameraServer->StartAutomaticCapture("cam0");
	}

	void Autonomous()
	{
	}


	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			printf("%d\n", m_CameraServer->IsAutoCaptureStarted());
		}
	}

	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot);
