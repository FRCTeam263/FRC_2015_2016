#include "LiftSystem.h"

LiftSystem::LiftSystem(void){
	toteLiftMotor1 = new CANTalon(SHORT_LIFT_MOTOR_1);
	toteLiftMotor2 = new CANTalon(SHORT_LIFT_MOTOR_2);
	canLiftMotor = new CANTalon(CAN_LIFT_MOTOR);

	toteBottomLS = new DigitalInput(SHORT_BOTTOM_LS);
	toteTopLS = new DigitalInput(SHORT_TOP_LS);
	canBottomLS = new DigitalInput(CAN_BOTTOM_LS);
	canTopLS = new DigitalInput(CAN_TOP_LS);

	utilities = new Utilities();
	toteLifterOutput = new ElevatorSpeedAlgorithm();
	canLifterOutput = new ElevatorSpeedAlgorithm(0.1, 0.01, 25, 0.7, 0.5, 0.005, 5, 5);

	toteLiftMotor1->SetFeedbackDevice(CANTalon::QuadEncoder);
	toteLiftMotor1->SetSensorDirection(true);
	canLiftMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	canLiftMotor->SetSensorDirection(true);

	toteLiftMotor1->SetPosition(0);
	toteLiftMotor1->Set(0);
	toteLiftMotor2->Set(0);
	canLiftMotor->SetPosition(0);
	canLiftMotor->Set(0);

	toteEncoderDistance = toteLiftMotor1->GetPosition();
	canEncoderDistance = canLiftMotor->GetPosition();
}

LiftSystem::~LiftSystem(void){
	delete toteLiftMotor1;
	delete toteLiftMotor2;
	delete canLiftMotor;

	delete toteBottomLS;
	delete toteTopLS;
	delete canBottomLS;
	delete canTopLS;

	delete utilities;
	delete toteLifterOutput;
	delete canLifterOutput;
}

void LiftSystem::RunLifter(Joystick *gamePad, Joystick *drivePad){
	static bool toteManualEnabled = true;
	static bool canManualEnabled = true;
	static int ShortLevel = 0;
	static int CanLevel = 0;
	static int targetCount = 0;
	float canMotorOutput = 0;
	float shortMotorOutput = 0;
	static bool lifterToggle = false;
	static float LockedInValue = 0;

	utilities->LimitSwitchRumble(drivePad, toteBottomLS);
	printf("Encoder: %f\n", toteLiftMotor1->GetPosition());

	if(utilities->GetJoystickButton(10, gamePad)){
		lifterToggle = !lifterToggle;
	}

	if(toteBottomLS->Get() == true){
		toteLiftMotor1->SetPosition(0);
	}
	if(canBottomLS->Get() == true){
		canLiftMotor->SetPosition(0);
	}
	if(toteTopLS->Get() == true){
		toteLiftMotor1->SetPosition(4500);
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
		canLiftMotor->Set(0.7);
		canManualEnabled = true;
	}
	else if((canBottomLS->Get() == false || canBottomLS->Get() == true) && gamePad->GetRawButton(7)){
		canLiftMotor->Set(-1);
		canManualEnabled = true;
	}
	else{
		if(canManualEnabled){
			canLiftMotor->Set(0);
		}
	}

	if(toteBottomLS->Get() == true && gamePad->GetRawButton(8) == true){
		toteLiftMotor1->Set(0);
		toteLiftMotor2->Set(0);
		toteLiftMotor1->SetPosition(0);
		LockedInValue = 0;
		toteManualEnabled = true;
	}
	else if(toteTopLS->Get() == true && gamePad->GetRawButton(9) == true){
		toteLiftMotor1->Set(0);
		toteLiftMotor2->Set(0);
		LockedInValue = 0;
		toteManualEnabled = true;
	}
	else if((toteTopLS->Get() == false || toteTopLS->Get() == true) && gamePad->GetRawButton(8)){
		if(lifterToggle == true){
			toteLiftMotor1->Set(0.3);
			toteLiftMotor2->Set(0.3);
		}
		else if(lifterToggle == false){
			toteLiftMotor1->Set(0.4);
			toteLiftMotor2->Set(0.4);
		}
		LockedInValue = 0;
		toteManualEnabled = true;
	}
	else if((toteBottomLS->Get() == false || toteBottomLS->Get() == true) && gamePad->GetRawButton(9)){
		if(lifterToggle == true){
			toteLiftMotor1->Set(-0.65);
			toteLiftMotor2->Set(-0.65);
		}
		else if(lifterToggle == false){
			toteLiftMotor1->Set(-1);
			toteLiftMotor2->Set(-1);
		}
		LockedInValue = 0;
		toteManualEnabled = true;
	}
	else if((gamePad->GetRawButton(8) == false && gamePad->GetRawButton(9) == false) && toteManualEnabled == true){
		if(LockedInValue == 0){
			LockedInValue = toteLiftMotor1->GetPosition();
		}
		else if(LockedInValue > 0){
			SetToteSpeed(toteLifterOutput->ComputeNextMotorSpeedCommand(toteLiftMotor1->GetPosition(), LockedInValue));
		}
		else{
			toteLiftMotor1->Set(0);
			toteLiftMotor2->Set(0);
		}

	}
	else{
	}

	if(gamePad->GetRawButton(11) == true){
		ShortLevel = 0;
		toteManualEnabled = false;
		LockedInValue = 0;
		targetCount = elevatorShortLevels[ShortLevel];
	}
	else if(gamePad->GetRawButton(12) == true){
		ShortLevel = 1;
		toteManualEnabled = false;
		LockedInValue = 0;
		targetCount = elevatorShortLevels[ShortLevel];
	}
	else if(gamePad->GetRawButton(13) == true){//1 tote high
		ShortLevel = 2;
		toteManualEnabled = false;
		LockedInValue = 0;
		targetCount = elevatorShortLevels[ShortLevel];
	}
	else if(gamePad->GetRawButton(14) == true){
		ShortLevel = 3;
		toteManualEnabled = false;
		LockedInValue = 0;
		targetCount = elevatorShortLevels[ShortLevel];
	}
	else if(gamePad->GetRawButton(15) == true){
		ShortLevel = 4;
		toteManualEnabled = false;
		LockedInValue = 0;
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

		targetCount = utilities->MaxValue(targetCount, 0, 4500);

		//printf("Target: %d\n", targetCount);

		shortMotorOutput = toteLifterOutput->ComputeNextMotorSpeedCommand(toteLiftMotor1->GetPosition(), targetCount);

		if(toteTopLS->Get() == true && shortMotorOutput > 0){
			shortMotorOutput = 0;
		}
		else if(toteBottomLS->Get() == true && shortMotorOutput < 0){
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
	if(toteBottomLS->Get() == false){
		toteLiftMotor1->Set(1);
	}
	else if(toteBottomLS->Get() == true){
		toteLiftMotor1->Set(0);
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
	toteLiftMotor1->Set(Speed * -1);
	toteLiftMotor2->Set(Speed * -1);
}

void LiftSystem::SetZero(void){
	canLiftMotor->Set(0);
	toteLiftMotor1->Set(0);
	toteLiftMotor2->Set(0);
}

