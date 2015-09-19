#include "MechanumDrive.h"
#include <math.h>

extern Joystick *twistStick;
extern Joystick *driveStick;


MechanumDrive::MechanumDrive(void)
{
	gyroSensor = new Gyro(1);	
	
	frontLeftMotor = new Victor(FRONT_LEFT_MOTOR);
	frontRightMotor = new Victor(FRONT_RIGHT_MOTOR);
	backLeftMotor = new Victor(BACK_LEFT_MOTOR);
	backRightMotor = new Victor(BACK_RIGHT_MOTOR);
	utilities = new Utilities();
	
	gyroSensor->SetSensitivity(0.007);
	
	//gyroSensor->Reset();
	
	SetupDrive();

}
MechanumDrive::~MechanumDrive(void)
{	
	delete frontLeftMotor;
	delete frontRightMotor;
	delete backLeftMotor;
	delete backRightMotor;
}
void MechanumDrive::Drive(void)
{
	float StrafeX = twistStick->GetX() * (twistStick->GetZ() - 1.5);
	float StrafeY = twistStick->GetY() * (twistStick->GetZ() - 1.5) / -1;
		
	float Twist = twistStick->GetTwist() * (twistStick->GetZ() - 1.5);

	if(fabs(Twist) < 0.15)
		Twist = 0;
	if(fabs(StrafeX) < 0.15)
		StrafeX = 0;
	if(fabs(StrafeY) < 0.15)	
		StrafeY = 0;

	float angle = gyroSensor->GetAngle() * -1;

	if(twistStick->GetRawButton(5)){
		gyroSensor->Reset();
	}

	if(angle < 0){
		angle = angle + 360;
	}

	//printf("Angle: %f\n", angle);

	float temp = StrafeY * cos(angle *(PI/180)) - StrafeX * sin(angle * (PI/180));
	StrafeX = StrafeY * sin(angle * (PI/180)) - StrafeX * cos(angle * (PI/180));
	StrafeY = temp;

	MechanumCalculations(StrafeX, StrafeY, Twist);
	Equalize();

	frontLeftSpeed = utilities->deadbandValue(frontLeftSpeed, 0.2);
	backLeftSpeed = utilities->deadbandValue(backLeftSpeed, 0.2);
	frontRightSpeed = utilities->deadbandValue(frontRightSpeed, 0.2);
	backRightSpeed = utilities->deadbandValue(backRightSpeed, 0.2);
	
	UINT syncGroup = 0x80;

	//printf("FL: %f BL: %f FR: %f BR: %f\n", frontLeftMotor->Get(), backLeftMotor->Get(), frontRightMotor->Get(), backRightMotor->Get());
	//printf("Angle: %f\n", gyroSensor->GetAngle());
	frontLeftMotor->Set(frontLeftSpeed * -1, syncGroup);
	frontRightMotor->Set(frontRightSpeed, syncGroup);
	backLeftMotor->Set(backLeftSpeed * -1, syncGroup);
	backRightMotor->Set(backRightSpeed, syncGroup);
	
	//printf("FRW: %f\t FRS: %f\n", frontRightMotor->Get(), frontRightSpeed);
}
void MechanumDrive::MechanumCalculations(float x, float y, float rotation)
{
	double xIn = x;
	double yIn = y;

	yIn = -yIn;

	frontLeftSpeed = xIn + yIn + rotation;
	frontRightSpeed = -xIn + yIn - rotation;
	backLeftSpeed = -xIn + yIn + rotation;
	backRightSpeed = xIn + yIn - rotation;
}
void MechanumDrive::Equalize()
{
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

void MechanumDrive::SetupDrive(void)
{
	frontLeftMotor->SetSafetyEnabled(false);
	frontRightMotor->SetSafetyEnabled(false);
	backLeftMotor->SetSafetyEnabled(false);
	backRightMotor->SetSafetyEnabled(false);
}

void MechanumDrive::AutonDrive(void){
	float StrafeX = 0;
	float StrafeY = -0.3;
	float Twist = gyroSensor->GetAngle() * 3 / 180;

	float angle = gyroSensor->GetAngle() * -1;

	if(angle < 0){
		angle = angle + 360;
	}

	float temp = StrafeY * cos(angle *(PI/180)) - StrafeX * sin(angle * (PI/180));
	StrafeX = StrafeY * sin(angle * (PI/180)) - StrafeX * cos(angle * (PI/180));
	StrafeY = temp;

	MechanumCalculations(StrafeX, StrafeY, Twist);
	Equalize();

	frontLeftSpeed = utilities->deadbandValue(frontLeftSpeed, 0.2);
	backLeftSpeed = utilities->deadbandValue(backLeftSpeed, 0.2);
	frontRightSpeed = utilities->deadbandValue(frontRightSpeed, 0.2);
	backRightSpeed = utilities->deadbandValue(backRightSpeed, 0.2);

	UINT syncGroup = 0x80;

	frontLeftMotor->Set(frontLeftSpeed * -1, syncGroup);
	frontRightMotor->Set(frontRightSpeed, syncGroup);
	backLeftMotor->Set(backLeftSpeed * -1, syncGroup);
	backRightMotor->Set(backRightSpeed, syncGroup);
}

/*
void MechanumDrive::RunGyro(void){
	
	static double prevAngle = 0.0;
	static bool bJumped = false;
	angle = gyroSensor->GetAngle();
	
	if(fabs(angle) < 0.1){
		angle = 0;
		gyroSensor->Reset();
	}
	if(fabs(angle) < 400)
	{
		filteredAngle = Utilities::lowPassFilterRealtime(angle, prevAngle, 100, 10); //lower 10 to make filter tighter
		if(fabs(filteredAngle) > 1000 && !bJumped)
		{
			bJumped = true;
			printf("Jump! values were angle = %3.3f and prevAngle = %3.3f\n", angle, prevAngle);
		}
		
		currentAngle = filteredAngle;
		prevAngle = filteredAngle;
		printf("Current Angle: %f\n", currentAngle);
	}
}

void MechanumDrive::RunGyroDigital(void *owner){
	MechanumDrive *drive = (MechanumDrive *)owner;
	drive->RunGyro();
}*/
