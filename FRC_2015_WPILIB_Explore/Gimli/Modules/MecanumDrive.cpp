#include "MecanumDrive.h"

extern Joystick *drivePad;
extern Joystick *gamePad;

MecanumDrive::MecanumDrive(void){
	FrontLeftMotor = new Victor(4);
	FrontRightMotor = new Victor(2);
	BackLeftMotor = new Victor(3);
	BackRightMotor = new Victor(1);
	
	utilities = new Utilities();

	RobotAngle = new Gyro(GYRO);
	RobotAngle->SetSensitivity(0.007); //multiple by .9. if more then 90% change, heading isnt right
	RobotAngle->Reset();
}

MecanumDrive::~MecanumDrive(void){
	delete FrontLeftMotor;
	delete FrontRightMotor;
	delete BackLeftMotor;
	delete BackRightMotor;
	delete utilities;
	delete RobotAngle;
}

void MecanumDrive::Drive(void){	
	float driveX = drivePad->GetX() * -1;
	float driveY = drivePad->GetY() * -1;
	float twist = drivePad->GetThrottle();
	
	float angle = RobotAngle->GetAngle() * -1;

	if(drivePad->GetRawButton(2)){
		RobotAngle->Reset();
	}
	
	if(angle < 0){
		angle = angle + 360;
	}
	
	driveX = utilities->deadbandValue(driveX, 0.2);
	driveY = utilities->deadbandValue(driveY, 0.2);
	twist = utilities->deadbandValue(twist, 0.2);
	angle = utilities->deadbandValue(angle, 10);

	if(drivePad->GetRawButton(1) || drivePad->GetRawButton(9)){
		angle = 0;
	}
	
	//printf("Gyro: %f\n", angle);
	
	/*float temp = driveY * cos(angle *(PI/180)) - driveX * sin(angle * (PI/180));
	driveX = driveY * sin(angle * (PI/180)) - driveX * cos(angle * (PI/180));
	driveY = temp;*/
	
	MecanumGyroDrive(driveX, driveY, twist);

	frontLeftSpeed = utilities->deadbandValue(frontLeftSpeed, 0.3);
	backLeftSpeed = utilities->deadbandValue(backLeftSpeed, 0.3);
	frontRightSpeed = utilities->deadbandValue(frontRightSpeed, 0.3);
	backRightSpeed = utilities->deadbandValue(backRightSpeed, 0.3);
	
	UINT syncGroup = 0x80;
	
	FrontLeftMotor->Set(frontLeftSpeed * -1, syncGroup);
	FrontRightMotor->Set(frontRightSpeed, syncGroup);
	BackLeftMotor->Set(backLeftSpeed * -1, syncGroup);
	BackRightMotor->Set(backRightSpeed, syncGroup);
}
void MecanumDrive::MecanumGyroDrive(float x, float y, float rotation){

	double xIn = x;
	double yIn = y;
	
	frontLeftSpeed = xIn + yIn + rotation;
	frontRightSpeed = -xIn + yIn - rotation;
	backLeftSpeed = -xIn + yIn + rotation;
	backRightSpeed = xIn + yIn - rotation;

	double Max = 0;

	if(fabs(frontLeftSpeed) > Max)
	{
		Max = fabs(frontLeftSpeed);
	}
	if(fabs(frontRightSpeed) > Max)
	{
		Max = fabs(frontRightSpeed);
	}
	if(fabs(backLeftSpeed) > Max)
	{
		Max = fabs(backLeftSpeed);
	}
	if(fabs(backRightSpeed) > Max)
	{
		Max = fabs(backRightSpeed);
	}
	if(Max > 1.0)
	{
		frontLeftSpeed = frontLeftSpeed / Max;
		frontRightSpeed = frontRightSpeed / Max;
		backLeftSpeed = backLeftSpeed / Max;
		backRightSpeed = backRightSpeed / Max;
	}
}
void MecanumDrive::SetUpDrive(void){
	FrontLeftMotor->SetSafetyEnabled(false);
	FrontRightMotor->SetSafetyEnabled(false);
	BackLeftMotor->SetSafetyEnabled(false);
	BackRightMotor->SetSafetyEnabled(false);
}
void MecanumDrive::AutonDrive(bool GyroEnabled, bool Forward){
	float driveX = 0;
	float driveY = 0.5;
	float twist = RobotAngle->GetAngle() * 3 / 180;

	float angle = RobotAngle->GetAngle() * -1;

	if(Forward == false){
		driveY = -0.5;
	}
	
	if(angle < 0){
		angle = angle + 360;
	}

	if(GyroEnabled){
		float temp = driveY * cos(angle *(PI/180)) - driveX * sin(angle * (PI/180));
		driveX = driveY * sin(angle * (PI/180)) - driveX * cos(angle * (PI/180));
		driveY = temp;
	}
	else if(GyroEnabled == false){
		twist = 0;
	}
	frontLeftSpeed = driveX + driveY + twist;
	frontRightSpeed = -driveX + driveY - twist;
	backLeftSpeed = -driveX + driveY + twist;
	backRightSpeed = driveX + driveY - twist;

	double Max = 0;
		
	if(fabs(frontLeftSpeed) > Max)
	{
		Max = fabs(frontLeftSpeed);
	}
	if(fabs(frontRightSpeed) > Max)
	{
		Max = fabs(frontRightSpeed);
	}
	if(fabs(backLeftSpeed) > Max)
	{
		Max = fabs(backLeftSpeed);
	}
	if(fabs(backRightSpeed) > Max)
	{
		Max = fabs(backRightSpeed);
	}
	if(Max > 1.0)
	{
		frontLeftSpeed = frontLeftSpeed / Max;
		frontRightSpeed = frontRightSpeed / Max;
		backLeftSpeed = backLeftSpeed / Max;
		backRightSpeed = backRightSpeed / Max;
	}

	UINT syncGroup = 0x80;

	FrontLeftMotor->Set(frontLeftSpeed * -1, syncGroup);
	FrontRightMotor->Set(frontRightSpeed, syncGroup);
	BackLeftMotor->Set(backLeftSpeed * -1, syncGroup);
	BackRightMotor->Set(backRightSpeed, syncGroup);
}

void MecanumDrive::AutonTurn(bool TurnLeft){
	float driveX = 0;
	float driveY = 0;
	float twist = 0.5;

	if(TurnLeft){
		twist = -0.5;
	}
	else if(TurnLeft == false){
		twist = 0.5;
	}
	
	frontLeftSpeed = driveX + driveY + twist;
	frontRightSpeed = -driveX + driveY - twist;
	backLeftSpeed = -driveX + driveY + twist;
	backRightSpeed = driveX + driveY - twist;

	double Max = 0;

	if(fabs(frontLeftSpeed) > Max)
	{
		Max = fabs(frontLeftSpeed);
	}
	if(fabs(frontRightSpeed) > Max)
	{
		Max = fabs(frontRightSpeed);
	}
	if(fabs(backLeftSpeed) > Max)
	{
		Max = fabs(backLeftSpeed);
	}
	if(fabs(backRightSpeed) > Max)
	{
		Max = fabs(backRightSpeed);
	}
	if(Max > 1.0)
	{
		frontLeftSpeed = frontLeftSpeed / Max;
		frontRightSpeed = frontRightSpeed / Max;
		backLeftSpeed = backLeftSpeed / Max;
		backRightSpeed = backRightSpeed / Max;
	}

	UINT syncGroup = 0x80;

	FrontLeftMotor->Set(frontLeftSpeed * -1, syncGroup);
	FrontRightMotor->Set(frontRightSpeed, syncGroup);
	BackLeftMotor->Set(backLeftSpeed * -1, syncGroup);
	BackRightMotor->Set(backRightSpeed, syncGroup);
}

void MecanumDrive::StopDrive(){
	UINT syncGroup = 0x80;
	
	FrontLeftMotor->Set(0, syncGroup);
	FrontRightMotor->Set(0, syncGroup);
	BackLeftMotor->Set(0, syncGroup);
	BackRightMotor->Set(0, syncGroup);
}
