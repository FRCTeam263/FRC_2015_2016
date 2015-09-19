#include "Shooter.h"

extern Joystick *gamePad;

Shooter::Shooter(void){
	ShooterMotor = new Victor(SHOOTER_MOTOR);
	SecondShooterMotor = new Victor(6);
	ShooterPot = new AnalogChannel(2);
	UltraSonicSensor = new AnalogChannel(4);
	ShooterLimitSwitch = new DigitalInput(2);
	LED = new Relay(3);

	utilities = new Utilities();
	//dashboard = new DashboardConnecter;

	ShooterPot->SetAverageBits(2);
	//visionsystem = new VisionSystem();
	ShooterOvershot = false;
	counter = 0;

	ds = DriverStation::GetInstance();
}

Shooter::~Shooter(void){
	delete ShooterMotor;
	delete SecondShooterMotor;
	delete UltraSonicSensor;
	delete ShooterPot;
	delete ds;
	delete LED;
	//delete visionsystem;
	delete utilities;
	//delete dashboard;
}

void Shooter::ShootBall(void){
	//visionsystem->RunVision();
	//float visionDistance = visionsystem->distance;
	ShooterAngle = ((float)ShooterPot->GetValue() - POT_MIN) / POT_MAX;
	ShooterAngle = utilities->deadbandValue(ShooterAngle, 0.001);
	ShooterAngle = utilities->boundValue(ShooterAngle, 0, 1.46);

	SonicSensorValue = (float)UltraSonicSensor->GetAverageVoltage();
//	const float VoltageToFeet = 512 / 5 / 12;  // Vcc of 5V divided by 512 gives inches.  Then div 12 to make feet.
//	float SonicSensorValueInFeet = SonicSensorValue * VoltageToFeet;

	const float SonarVoltsToFeet = 13.0 / 3.8;
	float SonicSensorValueInFeet = SonicSensorValue * SonarVoltsToFeet;

	SonicSensorValueInFeet = utilities->deadbandValue(SonicSensorValueInFeet, 1);
	ShooterAngle = utilities->deadbandValue(ShooterAngle, 0.009);

	SonicSensorValue = utilities->boundValue(SonicSensorValue, 0, 4.83);
	SonicSensorValue = SonicSensorValue / 0.009766;
	SonicSensorValue = SonicSensorValue / 12;

	static float POTSetpoint = 0.5;
	static int POTGate = 0;
	const long POTGateLimit = 128;

	if(ds->GetDigitalIn(7)){
		counter = 0;
	}

	if(ds->GetDigitalIn(1)){
		POTGate++;

		if(gamePad->GetRawButton(9)){
			if(POTGate > POTGateLimit){
				POTSetpoint = POTSetpoint - 0.01;
				POTGate = 0;
			}
		}
		else if(gamePad->GetRawButton(10)){
			if(POTGate > POTGateLimit){
				POTSetpoint = POTSetpoint + 0.01;
				POTGate = 0;
			}
		}
		if((!ds->GetDigitalIn(3) && ds->GetDigitalIn(4))){
			POTSetpoint = 0.2;
		}
		else if((!ds->GetDigitalIn(4) && ds->GetDigitalIn(3))){
			POTSetpoint = 0.7;
		}
	}
	else{
		float y, x, m, b;
		// m = (y2-y1)/(x2-x1)
		// y = mx + b => b = y - mx
		const float cm1 = (0.12-0.08)/(13.0-9.0);
		const float cb1 = 0.12 - cm1 * 13.0;
		const float cm2 = (0.13-0.12)/(13.5-13.0);
		const float cb2 = 0.13 - cm2 * 13.0;
		const float cm3 = (0.15-0.13)/(14.0-13.5);
		const float cb3 = 0.15 - cm3 * 13.5;


		x = SonicSensorValueInFeet;
		if (x < 13) {
			m = cm1;
			b = cb1;
		}
		else if (x < 13.5) {
			m = cm2;
			b = cb2;
		}
		else {
			m = cm3;
			b = cb3;
		}
		y = (m * x) + b;
		POTSetpoint = y;
	}
	printf("Sonic: %f\t POT: %f\t POTSetpoint: %f\t SonicFeet: %f\n", SonicSensorValue,
					ShooterAngle,
					POTSetpoint,
					SonicSensorValueInFeet);
	if(ShooterAngle > POTSetpoint){
		//LED->Set(Relay::kForward);
		ShooterOvershot = true;
	}
	else{
		//LED->Set(Relay::kOff);
		ShooterOvershot = false;
	}

	if(gamePad->GetRawButton(5)){
		ShooterMotor->Set(-0.5);
		SecondShooterMotor->Set(-0.5);
		/*if(ShooterOvershot == false && counter == 0){
			ShooterMotor->Set(-0.5);
			SecondShooterMotor->Set(-0.5);
		}
		while(counter < 665){
			if((ShooterOvershot) || (ShooterOvershot == false && counter > 0)){
				counter++;
				ShooterMotor->Set(1.0);
				SecondShooterMotor->Set(1.0);
				printf("Counter: %f\t POT: %f\n", counter, ShooterAngle);
			}
		}
		ShooterMotor->Set(0);
		SecondShooterMotor->Set(0);	*/
	}
	/*else{
		SecondShooterMotor->Set(0);
		ShooterMotor->Set(0);
	}*/
	

	else if(gamePad->GetRawButton(6)){
		ShooterMotor->Set(1.0);
		SecondShooterMotor->Set(1.0);
	}
	else{
		SecondShooterMotor->Set(0);
		ShooterMotor->Set(0);
	}

/*
	dashboard->AddData("SN", SonicSensorValueInFeet);
	dashboard->AddData("POTS", POTSetpoint);
	dashboard->SendData();
*/
}
void Shooter::StopShooter(void){
	ShooterMotor->Set(0);
	SecondShooterMotor->Set(0);
}
void Shooter::AutonShooterBackward(void){
	ShooterMotor->Set(-0.5);
	SecondShooterMotor->Set(-0.5);
}

void Shooter::AutonShooterForward(void){
	ShooterMotor->Set(1.0);
	SecondShooterMotor->Set(1.0);
}

/*#include "Shooter.h"

extern Joystick *gamePad;

Shooter::Shooter(void){
	ShooterMotor = new Victor(SHOOTER_MOTOR);
	SecondShooterMotor = new Victor(SHOOTER_MOTOR_2);
	ShooterPot = new AnalogChannel(SHOOTER_POT);
	UltraSonicSensor = new AnalogChannel(ULTRASONIC_SENSOR);
	ShooterLimitSwitch = new DigitalInput(LIMIT_SWITCH);
	shooterTimer = new Timer();
	ShooterEncoder = new Encoder(SHOOTER_ENCODER_A, SHOOTER_ENCODER_B, true, Encoder::k1X);//Yellow is B

	ShooterEncoder->SetDistancePerPulse(1.0);
	utilities = new Utilities();

	ds = DriverStation::GetInstance();

	ShooterPot->SetAverageBits(2);
	ShooterEncoder->Start();
	ShooterOvershot = false;
	counter = 0;
}

Shooter::~Shooter(void){
	delete ShooterMotor;
	delete SecondShooterMotor;
	delete UltraSonicSensor;
	delete ShooterLimitSwitch;
	delete shooterTimer;
	delete ShooterEncoder;
	delete ShooterPiston;
	delete ShooterPot;
}

void Shooter::ShootBall(void){
	ShooterAngle = ((float)ShooterPot->GetValue() - POT_MIN) / POT_MAX;
	ShooterAngle = utilities->deadbandValue(ShooterAngle, 0.001);
	ShooterAngle = utilities->boundValue(ShooterAngle, 0, 1.5);

	SonicSensorValue = (float)UltraSonicSensor->GetAverageVoltage();
	//	const float VoltageToFeet = 512 / 5 / 12;  // Vcc of 5V divided by 512 gives inches.  Then div 12 to make feet.
	//	float SonicSensorValueInFeet = SonicSensorValue * VoltageToFeet;

	const float SonarVoltsToFeet = 13.0 / 3.8;
	float SonicSensorValueInFeet = SonicSensorValue * SonarVoltsToFeet;


	SonicSensorValue = utilities->boundValue(SonicSensorValue, 0, 4.83);
	SonicSensorValue = SonicSensorValue / 0.009766;
	SonicSensorValue = SonicSensorValue / 12;

	static float POTSetpoint = 0.5;
	static int POTGate = 0;
	const long POTGateLimit = 128;

	if(ds->GetDigitalIn(7)){
		counter = 0;
	}
	// While button is in on position
	if(ds->GetDigitalIn(1)){
		POTGate++;

		if(gamePad->GetRawButton(9)){
			if(POTGate > POTGateLimit){
				POTSetpoint = POTSetpoint - 0.01;
				POTGate = 0;
			}
		}
		else if(gamePad->GetRawButton(10)){
			if(POTGate > POTGateLimit){
				POTSetpoint = POTSetpoint + 0.01;
				POTGate = 0;
			}
		}
	}
	else{
		struct MyRecordStruct {
		  float RangeInFeet;
		  float POTSetpointToUse;
		} MyRecord, MyRecords[10];
		MyRecord.RangeInFeet = 7.6;
		MyRecords[3].RangeInFeet = 7.7; 

		float y, x, m, b;
		// m = (y2-y1)/(x2-x1)
		// y = mx + b => b = y - mx
		const float cm1 = (0.12-0.08)/(13.0-9.0);
		const float cb1 = 0.12 - cm1 * 13.0;
		const float cm2 = (0.13-0.12)/(13.5-13.0);
		const float cb2 = 0.13 - cm2 * 13.0;
		const float cm3 = (0.15-0.13)/(14.0-13.5);
		const float cb3 = 0.15 - cm3 * 13.5;

		x = SonicSensorValueInFeet;
		if (x < 13) {
			m = cm1;
			b = cb1;
		}
		else if (x < 13.5) {
			m = cm2;
			b = cb2;
		}
		else {
			m = cm3;
			b = cb3;
		}
		y = (m * x) + b;
		POTSetpoint = y;
	}
	printf("Sonic: %f\t POT: %f\t POTSetpoint: %f\t SonicFeet: %f\n", SonicSensorValue,
			ShooterAngle,
			POTSetpoint,
			SonicSensorValueInFeet);
	if((ShooterAngle > POTSetpoint)){
		ShooterOvershot = true;
	}
	else{
		ShooterOvershot = false;
	}

	if(gamePad->GetRawButton(5)){
		if(ShooterOvershot == false && counter == 0){
			ShooterMotor->Set(-0.5);
			SecondShooterMotor->Set(-0.5);
		}
		while(counter < 665){
			if((ShooterOvershot) || (ShooterOvershot == false && counter > 0)){
				counter++;
				ShooterMotor->Set(1.0);
				SecondShooterMotor->Set(1.0);
				printf("Counter: %f\t POT: %f\n", counter, ShooterAngle);
			}
		}
		ShooterMotor->Set(0);
		SecondShooterMotor->Set(0);	
	}
	else{
		SecondShooterMotor->Set(0);
		ShooterMotor->Set(0);
	}
}
void Shooter::AutonShooter(void){
	ShooterAngle = ((float)ShooterPot->GetValue() - POT_MIN) / POT_MAX;
	ShooterAngle = utilities->deadbandValue(ShooterAngle, 0.001);
	ShooterAngle = utilities->boundValue(ShooterAngle, 0, 1.5);

	if((ShooterAngle > 0.24 && (ShooterAngle <= 1.5 || ShooterLimitSwitch->Get()))){
		ShooterOvershot = true;
	}
	else{
		ShooterOvershot = false;
	}

	if(ShooterOvershot == false && counter == 0){
		ShooterMotor->Set(-0.5);
		SecondShooterMotor->Set(-0.5);
	}
	else if(ShooterOvershot){
		do{
			counter++;
			ShooterMotor->Set(1.0);
			SecondShooterMotor->Set(1.0);
			printf("Counter: %f\t POT: %f\n", counter, ShooterAngle);
		}while(counter < 500);
		ShooterMotor->Set(0);
		SecondShooterMotor->Set(0);
	}
	else{
		ShooterMotor->Set(0);
		SecondShooterMotor->Set(0);
	}
}

void Shooter::StopShooter(void){
	ShooterMotor->Set(0);
	SecondShooterMotor->Set(0);
}
*/
