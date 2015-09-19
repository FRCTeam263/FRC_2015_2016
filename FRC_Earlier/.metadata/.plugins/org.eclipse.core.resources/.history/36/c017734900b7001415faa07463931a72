#include "LiftSystem.h"

LiftSystem::LiftSystem(void){
	shortLiftMotor1 = new CANTalon(SHORT_LIFT_MOTOR_1);
	shortLiftMotor2 = new CANTalon(SHORT_LIFT_MOTOR_2);
	canLiftMotor = new CANTalon(CAN_LIFT_MOTOR);

	shortBottomLS = new DigitalInput(SHORT_BOTTOM_LS);
	shortTopLS = new DigitalInput(SHORT_TOP_LS);
	canBottomLS = new DigitalInput(CAN_BOTTOM_LS);
	canTopLS = new DigitalInput(CAN_TOP_LS);
	toteTouchSensor = new DigitalInput(LONG_TOTE_SENSOR);
	canTouchSensor = new DigitalInput(SHORT_TOTE_SENSOR);

	utilities = new Utilities();
	toteLifterOutput = new ElevatorSpeedAlgorithm();
	canLifterOutput = new ElevatorSpeedAlgorithm(0.1, 0.01, 25, 0.7, 0.5, 0.005, 5, 5);

	shortLiftMotor1->SetFeedbackDevice(CANTalon::QuadEncoder);
	shortLiftMotor1->SetSensorDirection(true);
	canLiftMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	canLiftMotor->SetSensorDirection(true);

	shortLiftMotor1->SetPosition(0);
	canLiftMotor->SetPosition(0);

	toteEncoderDistance = shortLiftMotor1->GetPosition();
	canEncoderDistance = canLiftMotor->GetPosition();
}

LiftSystem::~LiftSystem(void){
	delete shortLiftMotor1;
	delete shortLiftMotor2;
	delete canLiftMotor;

	delete shortBottomLS;
	delete shortTopLS;
	delete canBottomLS;
	delete canTopLS;
	delete toteTouchSensor;
	delete canTouchSensor;

	delete utilities;
	delete toteLifterOutput;
	delete canLifterOutput;
}

void LiftSystem::RunLifter(Joystick *gamePad){
	static bool toteManualEnabled = true;
	static bool canManualEnabled = true;
	static int ShortLevel = 0;
	static int CanLevel = 0;
	static int targetCount = 0;
	float canMotorOutput = 0;
	float shortMotorOutput = 0;
	static bool lifterToggle = false;

	if(utilities->GetJoystickButton(10, gamePad)){
		lifterToggle = !lifterToggle;
	}

	if(shortBottomLS->Get() == true){
		shortLiftMotor1->SetPosition(0);
	}
	if(canBottomLS->Get() == true){
		canLiftMotor->SetPosition(0);
	}

	if(canBottomLS->Get() == true && gamePad->GetRawButton(6)){
		canLiftMotor->Set(0);
		canLiftMotor->SetPosition(0);
		canManualEnabled = true;
	}
	else if(canTopLS->Get() == true && gamePad->GetRawButton(7)){
		canLiftMotor->Set(0);
		canManualEnabled = true;
	}
	else if((canTopLS->Get() == false || canTopLS->Get() == true) && gamePad->GetRawButton(6)){
		if(lifterToggle == true){
			canLiftMotor->Set(0.3);
		}
		else if(lifterToggle == false){
			canLiftMotor->Set(0.55);
		}
		canManualEnabled = true;
	}
	else if((canBottomLS->Get() == false || canBottomLS->Get() == true) && gamePad->GetRawButton(7)){

		if(lifterToggle == true){
			canLiftMotor->Set(-0.7);
		}
		else if(lifterToggle == false){
			canLiftMotor->Set(-1);
		}
		canManualEnabled = true;
	}
	else{
		if(canManualEnabled){
			canLiftMotor->Set(0);
		}
	}

	if(shortBottomLS->Get() == true && gamePad->GetRawButton(8) == true){
		shortLiftMotor1->Set(0);
		shortLiftMotor2->Set(0);
		shortLiftMotor1->SetPosition(0);
		toteManualEnabled = true;
	}
	else if(shortTopLS->Get() == true && gamePad->GetRawButton(9) == true){
		shortLiftMotor1->Set(0);
		shortLiftMotor2->Set(0);
		toteManualEnabled = true;
	}
	else if((shortTopLS->Get() == false || shortTopLS->Get() == true) && gamePad->GetRawButton(8)){
		if(lifterToggle == true){
			shortLiftMotor1->Set(0.3);
			shortLiftMotor2->Set(0.3);
		}
		else if(lifterToggle == false){
			shortLiftMotor1->Set(0.5);
			shortLiftMotor2->Set(0.5);
		}
		toteManualEnabled = true;
	}
	else if((shortBottomLS->Get() == false || shortBottomLS->Get() == true) && gamePad->GetRawButton(9)){
		if(lifterToggle == true){
			shortLiftMotor1->Set(-0.65);
			shortLiftMotor2->Set(-0.65);
		}
		else if(lifterToggle == false){
			shortLiftMotor1->Set(-1);
			shortLiftMotor2->Set(-1);
		}
		toteManualEnabled = true;
	}
	else{
		if(toteManualEnabled){
			shortLiftMotor1->Set(0);
			shortLiftMotor2->Set(0);
		}
	}

	/*else if(shortTopLS->Get() == true){
			shortLiftMotor1->SetPosition(3830);
		}*/

	if(gamePad->GetRawButton(11) == true){
		ShortLevel = 0;
		toteManualEnabled = false;
		targetCount = elevatorShortLevels[ShortLevel];
	}
	else if(gamePad->GetRawButton(12) == true){
		ShortLevel = 1;
		toteManualEnabled = false;
		targetCount = elevatorShortLevels[ShortLevel];
	}
	else if(gamePad->GetRawButton(13) == true){//1 tote high
		ShortLevel = 2;
		toteManualEnabled = false;
		targetCount = elevatorShortLevels[ShortLevel];
	}
	else if(gamePad->GetRawButton(14) == true){
		ShortLevel = 3;
		toteManualEnabled = false;
		targetCount = elevatorShortLevels[ShortLevel];
	}
	else if(gamePad->GetRawButton(15) == true){
		ShortLevel = 4;
		toteManualEnabled = false;
		targetCount = elevatorShortLevels[ShortLevel];
	}

	if(gamePad->GetRawButton(1) == true){
		CanLevel = 0;
		canManualEnabled = false;
	}
	else if(gamePad->GetRawButton(2) == true){
		CanLevel = 1;
		canManualEnabled = false;
	}
	else if(gamePad->GetRawButton(3) == true){
		CanLevel = 2;
		canManualEnabled = false;
	}
	else if(gamePad->GetRawButton(4) == true){
		CanLevel = 3;
		canManualEnabled = false;
	}

	if(toteManualEnabled == false){

		if(gamePad->GetRawButton(17)){
			targetCount = targetCount + 30;
		}
		else if(gamePad->GetRawButton(18)){
			targetCount = targetCount - 30;
		}

		targetCount = utilities->MaxValue(targetCount, 0, 3850);

		//printf("Target: %d\n", targetCount);

		shortMotorOutput = toteLifterOutput->ComputeNextMotorSpeedCommand(shortLiftMotor1->GetPosition(), targetCount);

		if(shortTopLS->Get() == true && shortMotorOutput > 0){
			shortMotorOutput = 0;
		}
		else if(shortBottomLS->Get() == true && shortMotorOutput < 0){
			shortMotorOutput = 0;
		}

		SetToteSpeed(shortMotorOutput);
	}

	if(canManualEnabled == false){
		canMotorOutput = canLifterOutput->ComputeNextMotorSpeedCommand(canLiftMotor->GetPosition(), elevatorCanLevels[CanLevel]);

		//printf("Encoder: %f\t CMO: %f\t Level: %d\n", canLiftMotor->GetPosition(), canMotorOutput, CanLevel);

		if(canBottomLS->Get() == true && canMotorOutput < 0){
			canMotorOutput = 0;
		}
		else if(canTopLS->Get() == true && canMotorOutput > 0){
			canMotorOutput = 0;
		}
		SetCanSpeed(canMotorOutput);
	}
}

void LiftSystem::ResetLifter(){
	if(shortBottomLS->Get() == false){
		shortLiftMotor1->Set(1);
	}
	else if(shortBottomLS->Get() == true){
		shortLiftMotor1->Set(0);
	}

	if(canBottomLS->Get() == false){
		canLiftMotor->Set(1);
	}
	else if(canBottomLS->Get() == true){
		canLiftMotor->Set(0);
	}
}

void LiftSystem::SetCanSpeed(float Speed){
	canLiftMotor->Set(Speed * -1);
}

void LiftSystem::SetToteSpeed(float Speed){
	shortLiftMotor1->Set(Speed * -1);
	shortLiftMotor2->Set(Speed * -1);
}

void LiftSystem::SetZero(void){
	canLiftMotor->Set(0);
	shortLiftMotor1->Set(0);
	shortLiftMotor2->Set(0);
}

