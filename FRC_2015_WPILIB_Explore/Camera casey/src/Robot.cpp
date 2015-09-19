#include "WPILib.h"

class Robot: public SampleRobot {
	AnalogInput *theSonicSensor;
	AnalogInput *canSonicSensor;

	DigitalInput *toteLifterSwitchUp;
	DigitalInput *toteLifterSwitchDown;
	DigitalInput *canLifterSwitchUp;
	DigitalInput *canLifterSwitchDown;
	DigitalInput *canCrashBrakes;

	CANTalon *shortLiftMotor1;
	CANTalon *longLiftMotor1;
public:
	Robot() {
		theSonicSensor = new AnalogInput(0);
		canSonicSensor = new AnalogInput(1);

		toteLifterSwitchUp = new DigitalInput(3);
		toteLifterSwitchDown = new DigitalInput(4);
		canLifterSwitchUp = new DigitalInput(5);
		canLifterSwitchDown = new DigitalInput(6);
		canCrashBrakes = new DigitalInput(7);

		shortLiftMotor1 = new CANTalon(4);
		longLiftMotor1 = new CANTalon(6);

		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
	}

	~Robot() {

		delete theSonicSensor;
		delete canSonicSensor;

		delete toteLifterSwitchUp;
		delete toteLifterSwitchDown;
		delete canLifterSwitchUp;
		delete canLifterSwitchDown;
		delete canCrashBrakes;
		delete shortLiftMotor1;
		delete longLiftMotor1;
	}

	void Autonomous() {

	}
	void OperatorControl() {
		while (IsOperatorControl() && IsEnabled()) {
			SmartDashboard::PutNumber("SensorInFeet",
					theSonicSensor->GetAverageVoltage() * (512 / 5) / 12);

			SmartDashboard::PutString("Tote Limits",(toteLifterSwitchUp->Get())?"Top":(toteLifterSwitchDown->Get())?"Bottom":"");
			SmartDashboard::PutString("Can Limits",(canLifterSwitchUp->Get())?"Top":(canLifterSwitchDown->Get())?"Bottom":"");
			SmartDashboard::PutString("Can Brake",(canCrashBrakes->Get())?"Hit":"");

			SmartDashboard::PutNumber("Tote Position",shortLiftMotor1->GetPosition());
			SmartDashboard::PutNumber("Can Position",longLiftMotor1->GetPosition());

		}
	}

	void Test() {

	}
};

START_ROBOT_CLASS(Robot);
