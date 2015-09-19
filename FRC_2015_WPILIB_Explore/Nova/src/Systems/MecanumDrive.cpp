#include "MecanumDrive.h"

MecanumDrive::MecanumDrive(){
	FRMotor = new CANTalon(1);
	FLMotor = new CANTalon(3);
	BRMotor = new CANTalon(2);
	BLMotor = new CANTalon(0);

	FLMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	BLMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	FRMotor->SetFeedbackDevice(CANTalon::QuadEncoder);
	BRMotor->SetFeedbackDevice(CANTalon::QuadEncoder);

	FLWheel = new Encoder(0, 1, false, Encoder::k4X);
	/*BLWheel = new Encoder(2, 3, false, Encoder::k1X);
	FRWheel = new Encoder(4, 5, false, Encoder::k1X);
	BRWheel = new Encoder(6, 7, false, Encoder::k1X);*/

	mecanumGyro = new Gyro(0);
	mecanumGyro->SetSensitivity(0.007);

	utilities = new Utilities();

	FRMotor->Set(0);
	BRMotor->Set(0);
	FLMotor->Set(0);
	BLMotor->Set(0);

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

	delete FLWheel;

	delete utilities;

}

void MecanumDrive::Drive(Joystick *drivePad){
	float YDrive;
	float XDrive;
	float Rotate;

	static int ThrottleEnabled = 0;

	if(drivePad->GetRawButton(1)){
		ThrottleEnabled = 1;
	}
	if(drivePad->GetRawButton(2)){
		ThrottleEnabled = 0;
	}

	if(ThrottleEnabled == 1){
		YDrive = drivePad->GetY() / 2.2;
		XDrive = (drivePad->GetX() * -1) / 2.2;
		Rotate = (-drivePad->GetThrottle() + drivePad->GetTwist()) / 2.2;
	}
	else if(ThrottleEnabled == 0){
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

	FLMotor->Set(FLSpeed * -1);
	FRMotor->Set(FRSpeed);
	BLMotor->Set(BLSpeed * -1);
	BRMotor->Set(BRSpeed);
}

void MecanumDrive::AutonDriveStraight(bool GyroEnabled, float Speed){
	float driveX = 0;
	float driveY = Speed;
	float twist = mecanumGyro->GetAngle() * 3 / 180;

	float angle = mecanumGyro->GetAngle() * -1;

	if(angle < 0){
		angle = angle + 360;
	}

	if(GyroEnabled){
		float temp = driveY * cos(angle *(M_PIl/180)) - driveX * sin(angle * (M_PIl/180));
		driveX = driveY * sin(angle * (M_PIl/180)) - driveX * cos(angle * (M_PIl/180));
		driveY = temp;
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

	FLMotor->Set(FLSpeed * -1);
	FRMotor->Set(FRSpeed);
	BLMotor->Set(BLSpeed * -1);
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

	FLMotor->Set(FLSpeed * -1);
	FRMotor->Set(FRSpeed);
	BLMotor->Set(BLSpeed * -1);
	BRMotor->Set(BRSpeed);
}

void MecanumDrive::SetZero(void){
	FLMotor->Set(0);
	FRMotor->Set(0);
	BLMotor->Set(0);
	BRMotor->Set(0);
}
