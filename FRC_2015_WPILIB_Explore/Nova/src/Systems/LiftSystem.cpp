#include "LiftSystem.h"

LiftSystem::LiftSystem(void){
	shortLiftMotor1 = new CANTalon(4);
	shortLiftMotor2 = new CANTalon(5);
	longLiftMotor1 = new CANTalon(6);
	longLiftMotor2 = new VictorSP(7);

	leftWheel = new Talon(9);
	rightWheel = new Talon(8);

	liftMotor = new Victor(3);

	shortBottomLiftSystem = new DigitalInput(1);
	shortTopLiftSystem = new DigitalInput(2);
	longBottomLiftSystem = new DigitalInput(3);
	longTopLS = new DigitalInput(4);
	shortToteTouchSensor = new DigitalInput(5);
	longToteTouchSensor = new DigitalInput(5);

	utilities = new Utilities();
	shortPID = new AfterPID();
	longPID = new AfterPID();

	shortPID->SetPID(1, 0, 0);
	longPID->SetPID(1, 0, 0);

	shortLiftMotor1->SetFeedbackDevice(CANTalon::QuadEncoder);
	longLiftMotor1->SetFeedbackDevice(CANTalon::QuadEncoder);

	shortLiftMotor1->SetPosition(0);
	longLiftMotor1->SetPosition(0);

	shortLiftMotor1->Set(0);
	shortLiftMotor2->Set(0);
	longLiftMotor1->Set(0);
	longLiftMotor2->Set(0);
	leftWheel->Set(0);
	rightWheel->Set(0);

	shortEncoderDistance = shortLiftMotor1->GetPosition();
	longEncoderDistance = longLiftMotor1->GetPosition();
}

LiftSystem::~LiftSystem(void){
	delete shortLiftMotor1;
	delete shortLiftMotor2;
	delete longLiftMotor1;
	delete longLiftMotor2;

	delete shortBottomLiftSystem;
	delete shortTopLiftSystem;
	delete longBottomLiftSystem;
	delete longTopLS;
	delete shortToteTouchSensor;
	delete longToteTouchSensor;

	delete utilities;

	delete liftMotor;
}

void LiftSystem::TestLifter(Joystick *gamePad){
	if(gamePad->GetRawButton(5)){
		liftMotor->Set(0.5);
	}
	else if(gamePad->GetRawButton(6)){
		liftMotor->Set(-0.5);
	}
	else{
		liftMotor->Set(0);
	}
}

void LiftSystem::RunLongLift(Joystick *gamePad){



	float MotorOutput = 0;
	static float Counter = 0;
	static float LongLevel = 0;
	const long Limit = 128;

	if(longBottomLiftSystem->Get() == true){
		longLiftMotor1->Set(0);
		longLiftMotor2->Set(0);

		longLiftMotor1->SetPosition(0);
	}
	else{
		if(LongLevel > 2.5){
			LongLevel = 2.5;
		}
		if(LongLevel < 0){
			LongLevel= 0;
		}

		Counter++;
		if(gamePad->GetRawButton(4)){
			if(Counter > Limit){
				LongLevel = LongLevel + 1;
				Counter = 0;
			}
		}
		else if(gamePad->GetRawButton(3)){
			if(Counter > Limit){
				LongLevel = LongLevel - 1;
				Counter = 0;
			}
		}
		else if(gamePad->GetRawButton(2)){
			if(Counter > Limit){
				LongLevel = LongLevel + 0.5;
				Counter = 0;
			}
		}
		else if(gamePad->GetRawButton(1)){
			if(Counter > Limit){
				LongLevel = LongLevel - 0.5;
				Counter = 0;
			}
		}
		else if(gamePad->GetRawButton(6)){
			if(Counter > Limit){
				LongLevel = 2;
				Counter = 0;
			}
		}

		if(LongLevel == 0.5){
			MotorOutput = longPID->GetOutput(longEncoderDistance, 0.5, 10, true);
		}
		else if(LongLevel == 1){
			MotorOutput = longPID->GetOutput(longEncoderDistance, 1, 10, true);
		}
		else if(LongLevel == 1.5){
			MotorOutput = longPID->GetOutput(longEncoderDistance, 1.5, 10, true);
		}
		else if(LongLevel == 2){
			MotorOutput = longPID->GetOutput(longEncoderDistance, 2, 10, true);
		}
		else if(LongLevel == 2.5){
			MotorOutput = longPID->GetOutput(longEncoderDistance, 2.5, 10, true);
		}
		else{
			MotorOutput = 0;
		}
	}
	longLiftMotor1->Set(MotorOutput);
	longLiftMotor2->Set(MotorOutput);

}

void LiftSystem::RunShortLift(Joystick *gamePad){
	if(gamePad->GetRawAxis(2) > 0.2){
		leftWheel->Set(-1);
		rightWheel->Set(1);
	}
	else{
		leftWheel->Set(0);
		rightWheel->Set(0);
	}

	float MotorOutput = 0;

	static float Counter = 0;
	static float ShortLevel = 0;
	const long Limit = 128;

	if(shortTopLiftSystem->Get() == true){
		shortLiftMotor1->Set(0);
		shortLiftMotor2->Set(0);

		shortLiftMotor1->SetPosition(0);
	}
	else{
		if(ShortLevel > 2.5){
			ShortLevel = 2.5;
		}
		if(ShortLevel < 0){
			ShortLevel= 0;
		}

		Counter++;
		if(gamePad->GetPOV(90)){
			if(Counter > Limit){
				ShortLevel = ShortLevel + 1;
				Counter = 0;
			}
		}
		else if(gamePad->GetPOV(270)){
			if(Counter > Limit){
				ShortLevel = ShortLevel - 1;
				Counter = 0;
			}
		}
		else if(gamePad->GetPOV(0)){
			if(Counter > Limit){
				ShortLevel = ShortLevel + 0.5;
				Counter = 0;
			}
		}
		else if(gamePad->GetPOV(180)){
			if(Counter > Limit){
				ShortLevel = ShortLevel - 0.5;
				Counter = 0;
			}
		}
		else if(gamePad->GetRawAxis(2) > 0){
			if(Counter > Limit){
				ShortLevel = 2.5;
				Counter = 0;
			}
		}

		if(ShortLevel == 0.5){
			MotorOutput = longPID->GetOutput(longEncoderDistance, 0.5, 10, true);
		}
		else if(ShortLevel == 1){
			MotorOutput = longPID->GetOutput(longEncoderDistance, 1, 10, true);
		}
		else if(ShortLevel == 1.5){
			MotorOutput = longPID->GetOutput(longEncoderDistance, 1.5, 10, true);
		}
		else if(ShortLevel == 2){
			MotorOutput = longPID->GetOutput(longEncoderDistance, 2, 10, true);
		}
		else if(ShortLevel == 2.5){
			MotorOutput = longPID->GetOutput(longEncoderDistance, 2.5, 10, true);
		}
		else{
			MotorOutput = 0;
		}
	}

	shortLiftMotor1->Set(MotorOutput);
	shortLiftMotor2->Set(MotorOutput);
}

void LiftSystem::ResetLifter(){
	if(shortBottomLiftSystem->Get() == false){
		shortLiftMotor1->Set(-1);
		shortLiftMotor2->Set(-1);
	}
	else if(shortBottomLiftSystem->Get() == true){
		shortLiftMotor1->Set(0);
		shortLiftMotor2->Set(0);
	}

	if(longBottomLiftSystem->Get() == false){
		longLiftMotor1->Set(-1);
		longLiftMotor2->Set(-1);
	}
	else if(longBottomLiftSystem->Get() == true){
		longLiftMotor1->Set(0);
		longLiftMotor2->Set(0);
	}
}
