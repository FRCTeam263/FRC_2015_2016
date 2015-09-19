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
class Robot: public SampleRobot {
	AnalogInput *sonicSensor;
	Joystick *gamePad;
	Servo *exampleServo;
	DigitalInput *ls;
public:
	Robot() {
		sonicSensor = new AnalogInput(0);
		exampleServo = new Servo(7);
		gamePad = new Joystick(0);

		ls = new DigitalInput(0);
	}
	~Robot() {
		delete sonicSensor;
		delete exampleServo;
		delete gamePad;
	}

	void Autonomous() {

	}

	void OperatorControl() {
//		while(IsOperatorControl() && IsEnabled()){
//			if(ls->Get() == true){
//				printf("True\n");
//			}
//			else if(ls->Get() == false){
//				printf("False\n");
//			}
//		}
		printf("before while \n");
		int servoAngle = exampleServo->GetAngle();
		Wait(5);
		while (gamePad->GetRawButton(1)) {
			exampleServo->SetAngle(0);
			Wait(0.5);
			printf("start \n");
		}
		float SonicSensorValue = 0;
			exampleServo->SetAngle(180);
			while(servoAngle>0 && servoAngle<180)
			{
				SonicSensorValue = sonicSensor->GetVoltage();
							float SonicSensorValueInInches = SonicSensorValue * (512 / 5);
							printf("sonicReturn = %f,	inches = %f feet=%f	\n", SonicSensorValue,
							SonicSensorValueInInches, SonicSensorValueInInches / 12);
							Wait(.09);
			}
					printf("done \n");
		}



	void Test() {
	}
};

START_ROBOT_CLASS(Robot);
