#include "MecanumDrive.h"

MecanumDrive::MecanumDrive(){
	FRMotor = new CANTalon(FRONT_RIGHT_MOTOR);
	FLMotor = new CANTalon(FRONT_LEFT_MOTOR);
	BRMotor = new CANTalon(BACK_RIGHT_MOTOR);
	BLMotor = new CANTalon(BACK_LEFT_MOTOR);

	FLMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	BLMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	FRMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	BRMotor->SetFeedbackDevice(CANTalon::QuadEncoder);

	mecanumGyro = new Gyro(GYRO);
	mecanumGyro->SetSensitivity(0.007);
	mecanumGyro->Reset();

	utilities = new Utilities();
	turnOutput = new ElevatorSpeedAlgorithm(0.3, 0.02, 1, 1, 1, 0.0001, 2, 50);//0.1, 0.02, 1, 1, 1, 0.001, 2, 13
	//TODO need to check these values, dont remember if they work or not. Changing it to the values in autonomous

	FRMotor->Set(0);
	BRMotor->Set(0);
	FLMotor->Set(0);
	BLMotor->Set(0);
	FLMotor->SetPosition(0);
	FRMotor->SetPosition(0);
	BLMotor->SetPosition(0);
	BRMotor->SetPosition(0);

	FRMotor->SetSensorDirection(true);
	BRMotor->SetSensorDirection(true);

	FLSpeed = 0;
	FRSpeed = 0;
	BLSpeed = 0;
	BRSpeed = 0;
}

MecanumDrive::~MecanumDrive(){
	delete FRMotor;
	delete FLMotor;
	delete BLMotor;
	delete BRMotor;

	delete mecanumGyro;
	delete turnOutput;

	delete utilities;

}

void MecanumDrive::Drive(Joystick *drivePad){

	if(drivePad->GetRawButton(4)){
		FLMotor->SetPosition(0);
		FRMotor->SetPosition(0);
		BLMotor->SetPosition(0);
		BRMotor->SetPosition(0);
	}

	float YDrive;
	float XDrive;
	float Rotate;

	static bool ThrottleEnabled = true;

	if(utilities->GetJoystickButton(1, drivePad)){
		ThrottleEnabled = !ThrottleEnabled;
	}

	if(ThrottleEnabled == true){
		YDrive = drivePad->GetY() / 2.35;
		XDrive = (drivePad->GetX()  * -1) / 2.35;
		Rotate = (-drivePad->GetThrottle() + drivePad->GetTwist()) / 2.35;
	}
	else if(ThrottleEnabled == false){
		YDrive = drivePad->GetY();
		XDrive = drivePad->GetX() * -1;
		Rotate = -drivePad->GetThrottle() + drivePad->GetTwist();
	}

	//printf("Throttle: %f\t Twist: %f\t Trigger: %d\n", drivePad->GetThrottle(), drivePad->GetTwist(), drivePad->GetTrigger());

	YDrive = utilities->DeadBand(YDrive, 0.1);
	XDrive = utilities->DeadBand(XDrive, 0.1);
	Rotate = utilities->DeadBand(Rotate, 0.1);

	FLSpeed = XDrive + YDrive + Rotate;
	FRSpeed = -XDrive + YDrive - Rotate;
	BLSpeed = -XDrive + YDrive + Rotate;
	BRSpeed = XDrive + YDrive - Rotate;

	float max = 0;

	if(fabs(FLSpeed) > max){
		max = fabs(FLSpeed);
	}
	if(fabs(FRSpeed) > max){
		max = fabs(FRSpeed);
	}
	if(fabs(BLSpeed) > max){
		max = fabs(BLSpeed);
	}
	if(fabs(BRSpeed) > max){
		max = fabs(BRSpeed);
	}
	if(max > 1){
		FLSpeed = FLSpeed / max;
		FRSpeed = FRSpeed / max;
		BLSpeed = BLSpeed / max;
		BRSpeed = BRSpeed / max;
	}

	if(drivePad->GetRawButton(5) == true){
		//rotate around a point outside the robot instead of rotating around the center of the robot.
		if(ThrottleEnabled == true){
			FLMotor->Set(0);
			FRMotor->Set(0);
			BLMotor->Set(-0.35);
			BRMotor->Set(-0.35);
		}
		else if(ThrottleEnabled == false){
			FLMotor->Set(0);
			FRMotor->Set(0);
			BLMotor->Set(-0.7);
			BRMotor->Set(-0.7);
		}
	}
	else if(drivePad->GetRawButton(6) == true){
		if(ThrottleEnabled == true){
			FLMotor->Set(0);
			FRMotor->Set(0);
			BLMotor->Set(0.35);
			BRMotor->Set(0.35);
		}
		else if(ThrottleEnabled == false){
			FLMotor->Set(0);
			FRMotor->Set(0);
			BLMotor->Set(0.7);
			BRMotor->Set(0.7);
		}
	}
	else{
		FLMotor->Set(-FLSpeed);
		FRMotor->Set(FRSpeed);// / 1.02
		BLMotor->Set(-BLSpeed);
		BRMotor->Set(BRSpeed);// / 1.02
	}
}

void MecanumDrive::TurnToAngle(Joystick *drivePad){
	float Speed = 0;
	if(drivePad->GetRawButton(3)){
		if(mecanumGyro->GetAngle() < 285){
			Speed = -turnOutput->ComputeNextMotorSpeedCommand(mecanumGyro->GetAngle(), 285);
		}
		else if(mecanumGyro->GetAngle() > 285){
			Speed = turnOutput->ComputeNextMotorSpeedCommand(mecanumGyro->GetAngle(), 285);
		}
	}
	else if(drivePad->GetRawButton(4)){
		if(mecanumGyro->GetAngle() > -15){
			Speed = turnOutput->ComputeNextMotorSpeedCommand(mecanumGyro->GetAngle(), -15);
		}
		else if(mecanumGyro->GetAngle() < -15){
			Speed = -turnOutput->ComputeNextMotorSpeedCommand(mecanumGyro->GetAngle(), -15);
		}
	}
	AutonTurn(Speed / 1.5);
}

void MecanumDrive::AutonDriveStraight(bool GyroEnabled, float Speed, bool Strafe){
	float driveX;
	float driveY;

	if(Strafe == true){
		driveX = Speed;
		driveY = 0;
	}
	else if(Strafe == false){
		driveY = Speed;
		driveX = 0;
	}

	float twist = mecanumGyro->GetAngle() * 3 / 180;

	float angle = mecanumGyro->GetAngle() * -1;

	if(angle < 0){
		angle = angle + 360;
	}

	if(GyroEnabled && Strafe == false){
		float temp = driveY * cos(angle *(M_PIl/180)) - driveX * sin(angle * (M_PIl/180));
		driveX = driveY * sin(angle * (M_PIl/180)) - driveX * cos(angle * (M_PIl/180));
		driveY = temp;
	}
	else if(GyroEnabled && Strafe == true){
		float temp = driveX * cos(angle *(M_PIl/180)) - driveY * sin(angle * (M_PIl/180));
		driveY = driveX * sin(angle * (M_PIl/180)) - driveY * cos(angle * (M_PIl/180));
		driveX = temp;
	}
	else if(GyroEnabled == false){
		twist = 0;
	}
	FLSpeed = driveX + driveY + twist;
	FRSpeed = -driveX + driveY - twist;
	BLSpeed = -driveX + driveY + twist;
	BRSpeed = driveX + driveY - twist;

	double Max = 0;

	if(fabs(FLSpeed) > Max)
	{
		Max = fabs(FLSpeed);
	}
	if(fabs(FRSpeed) > Max)
	{
		Max = fabs(FRSpeed);
	}
	if(fabs(BLSpeed) > Max)
	{
		Max = fabs(BLSpeed);
	}
	if(fabs(BRSpeed) > Max)
	{
		Max = fabs(BRSpeed);
	}
	if(Max > 1.0)
	{
		FLSpeed = FLSpeed / Max;
		FRSpeed = FRSpeed / Max;
		BLSpeed = BLSpeed / Max;
		BRSpeed = BRSpeed / Max;
	}

	FLMotor->Set(-FLSpeed);
	FRMotor->Set(FRSpeed);
	BLMotor->Set(-BLSpeed);
	BRMotor->Set(BRSpeed);
}

void MecanumDrive::AutonTurn(float Speed){
	float driveX = 0;
	float driveY = 0;
	float twist = Speed;

	FLSpeed = driveX + driveY + twist;
	FRSpeed = -driveX + driveY - twist;
	BLSpeed = -driveX + driveY + twist;
	BRSpeed = driveX + driveY - twist;

	double Max = 0;

	if(fabs(FLSpeed) > Max)
	{
		Max = fabs(FLSpeed);
	}
	if(fabs(FRSpeed) > Max)
	{
		Max = fabs(FRSpeed);
	}
	if(fabs(BLSpeed) > Max)
	{
		Max = fabs(BLSpeed);
	}
	if(fabs(BRSpeed) > Max)
	{
		Max = fabs(BRSpeed);
	}
	if(Max > 1.0)
	{
		FLSpeed = FLSpeed / Max;
		FRSpeed = FRSpeed / Max;
		BLSpeed = BLSpeed / Max;
		BRSpeed = BRSpeed / Max;
	}

	FLMotor->Set(-FLSpeed);
	FRMotor->Set(FRSpeed);
	BLMotor->Set(-BLSpeed);
	BRMotor->Set(BRSpeed);
}

void MecanumDrive::SetZero(void){
	FLMotor->Set(0);
	FRMotor->Set(0);
	BLMotor->Set(0);
	BRMotor->Set(0);
}

int MecanumDrive::AverageEncoders(void){
	return (FLMotor->GetPosition() + FRMotor->GetPosition() + BLMotor->GetPosition() + BRMotor->GetPosition()) / 4;
}

int MecanumDrive::AverageTurnRightEncoders(void){
	return (FLMotor->GetPosition() + BLMotor->GetPosition() + -FRMotor->GetPosition() + -BRMotor->GetPosition()) / 4;
}

int MecanumDrive::AverageTurnLeftEncoders(void){
	return (-FLMotor->GetPosition() + -BLMotor->GetPosition() + FRMotor->GetPosition() + BRMotor->GetPosition()) / 4;
}

int MecanumDrive::AverageLeftStrafe(){
	return (-FLMotor->GetPosition() + BLMotor->GetPosition() + -BRMotor->GetPosition() + FRMotor->GetPosition()) / 4;
}

void MecanumDrive::ResetEncoders(void){
	FLMotor->SetPosition(0);
	FRMotor->SetPosition(0);
	BLMotor->SetPosition(0);
	BRMotor->SetPosition(0);
}
