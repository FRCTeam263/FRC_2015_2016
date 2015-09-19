#include "MecanumDrive.h"

MecanumDrive::MecanumDrive() {
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

	builtInAccel = new BuiltInAccelerometer();

	utilities = new Utilities();

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

	SnapshotOfGyroValue  = 0.0;
	SnapshotOfAccelerometerValueX  = 0.0;
	SnapshotOfAccelerometerValueY  = 0.0;
	SnapshotOfAccelerometerValueZ  = 0.0;

}

MecanumDrive::~MecanumDrive() {
	delete FRMotor;
	delete FLMotor;
	delete BLMotor;
	delete BRMotor;

	delete mecanumGyro;
	delete builtInAccel;

	delete utilities;

}

void MecanumDrive::Drive(Joystick *drivePad) {

	if (drivePad->GetRawButton(4)) {
		FLMotor->SetPosition(0);
		FRMotor->SetPosition(0);
		BLMotor->SetPosition(0);
		BRMotor->SetPosition(0);
	}

	float YDrive;
	float XDrive;
	float Rotate;

	static bool ThrottleEnabled = false;

	if (utilities->GetJoystickButton(1, drivePad)) {
		ThrottleEnabled = !ThrottleEnabled;
	}

	if (ThrottleEnabled == true) {
		YDrive = drivePad->GetY() / 2;
		XDrive = (drivePad->GetX() * -1) / 2;
		Rotate = (-drivePad->GetThrottle() + drivePad->GetTwist()) / 2;
	} else if (ThrottleEnabled == false) {
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

	if (fabs(FLSpeed) > max) {
		max = fabs(FLSpeed);
	}
	if (fabs(FRSpeed) > max) {
		max = fabs(FRSpeed);
	}
	if (fabs(BLSpeed) > max) {
		max = fabs(BLSpeed);
	}
	if (fabs(BRSpeed) > max) {
		max = fabs(BRSpeed);
	}
	if (max > 1) {
		FLSpeed = FLSpeed / max;
		FRSpeed = FRSpeed / max;
		BLSpeed = BLSpeed / max;
		BRSpeed = BRSpeed / max;
	}

	if (drivePad->GetRawButton(5) == true) {
		//rotate around a point outside the robot instead of rotating around the center of the robot.
		FLMotor->Set(0);
		FRMotor->Set(0);
		BLMotor->Set(-0.7);
		BRMotor->Set(-0.7 / 1.02);
	} else if (drivePad->GetRawButton(6) == true) {
		FLMotor->Set(0);
		FRMotor->Set(0);
		BLMotor->Set(0.7);
		BRMotor->Set(0.7 / 1.02);
	} else {
		FLMotor->Set(-FLSpeed);
		FRMotor->Set(FRSpeed / 1.02);
		BLMotor->Set(-BLSpeed);
		BRMotor->Set(BRSpeed / 1.02);
	}
}

void MecanumDrive::SnapshotAutonGyroAndAccelerometerValues(void) {

	SnapshotOfGyroValue = mecanumGyro->GetAngle();
	SnapshotOfAccelerometerValueX = builtInAccel->GetX();
	SnapshotOfAccelerometerValueY = builtInAccel->GetY();
	SnapshotOfAccelerometerValueZ = builtInAccel->GetZ();

}

void MecanumDrive::AutonDriveStraight(bool GyroEnabled, float Speed,
		bool Strafe) {
	float driveX;
	float driveY;

	if (Strafe == true) {
		driveX = Speed;
		driveY = 0;
	} else if (Strafe == false) {
		driveY = Speed;
		driveX = 0;
	}

	float twist = mecanumGyro->GetAngle() * 3 / 180;  // What is this doing?  Looks like call always set to false, not used.

	float angle = mecanumGyro->GetAngle() * -1;

	if (angle < 0) {
		angle = angle + 360;
	}
//	else if (angle >=360) {		// why isn't this added here?
//		angle = angle - 360;
//	}

	if (GyroEnabled && Strafe == false) {
		float temp = driveY * cos(angle * (M_PIl / 180))
				- driveX * sin(angle * (M_PIl / 180));
		driveX = driveY * sin(angle * (M_PIl / 180))
				- driveX * cos(angle * (M_PIl / 180));
		driveY = temp;
	} else if (GyroEnabled && Strafe == true) {
		float temp = driveX * cos(angle * (M_PIl / 180))
				- driveY * sin(angle * (M_PIl / 180));
		driveY = driveX * sin(angle * (M_PIl / 180))
				- driveY * cos(angle * (M_PIl / 180));
		driveX = temp;
	} else if (GyroEnabled == false) {
		twist = 0;
	}
	FLSpeed = driveX + driveY + twist;
	FRSpeed = -driveX + driveY - twist;
	BLSpeed = -driveX + driveY + twist;
	BRSpeed = driveX + driveY - twist;

	// Recalibrate the starting position any time the speed is set to zero.
	if ((-0.0005 < Speed) && (Speed < 0.0005)) {  // real # so can't assume 0 will be exact.
		SnapshotAutonGyroAndAccelerometerValues();
	}

	// Note: empirically, the Accelerometer takes just under 20 seconds to stabilize.  This
	// code assumes this has settled wasting for the competition round to start.  I think
	// the gyro was similar.

	// Processing: Straight Line Rotation Compensation
	const double GyroDivisorInDegrees = 90.0;  // derive via empirical trial and error
	double GyroErrorInDegrees = angle - SnapshotOfGyroValue;

	FLSpeed += GyroErrorInDegrees / GyroDivisorInDegrees * 1;
	FRSpeed += GyroErrorInDegrees / GyroDivisorInDegrees * -1;
	BLSpeed += GyroErrorInDegrees / GyroDivisorInDegrees * 1;
	BRSpeed += GyroErrorInDegrees / GyroDivisorInDegrees * -1;

	if (!Strafe) {
		// Processing: Straight Line Translation Compensation:
		// driving forward or backward, compensate drift in strafe axis.
		const double AccelerometerXDivisorInG = 0.3;  // derive via empirical trial and error
		double AccelerometerXErrorInG = builtInAccel->GetX()
				- SnapshotOfAccelerometerValueX;

		FLSpeed += AccelerometerXErrorInG / AccelerometerXDivisorInG * 1;
		FRSpeed += AccelerometerXErrorInG / AccelerometerXDivisorInG * -1;
		BLSpeed += AccelerometerXErrorInG / AccelerometerXDivisorInG * -1;
		BRSpeed += AccelerometerXErrorInG / AccelerometerXDivisorInG * 1;
	} else {
		// Processing: Straight Line Translation Compensation:
		// driving in a strafe direction, compensate drift in forward/backward axis.
		const double AccelerometerYDivisorInG = 0.3;  // derive via empirical trial and error
		double AccelerometerYErrorInG = builtInAccel->GetY()
				- SnapshotOfAccelerometerValueY;

		FLSpeed += AccelerometerYErrorInG / AccelerometerYDivisorInG * 1;
		FRSpeed += AccelerometerYErrorInG / AccelerometerYDivisorInG * 1;
		BLSpeed += AccelerometerYErrorInG / AccelerometerYDivisorInG * 1;
		BRSpeed += AccelerometerYErrorInG / AccelerometerYDivisorInG * 1;
	}

	double Max = 0;

	if (fabs(FLSpeed) > Max) {
		Max = fabs(FLSpeed);
	}
	if (fabs(FRSpeed) > Max) {
		Max = fabs(FRSpeed);
	}
	if (fabs(BLSpeed) > Max) {
		Max = fabs(BLSpeed);
	}
	if (fabs(BRSpeed) > Max) {
		Max = fabs(BRSpeed);
	}
	if (Max > 1.0) {
		FLSpeed = FLSpeed / Max;
		FRSpeed = FRSpeed / Max;
		BLSpeed = BLSpeed / Max;
		BRSpeed = BRSpeed / Max;
	}

	FLMotor->Set(-FLSpeed);
	FRMotor->Set(FRSpeed / 1.02);
	BLMotor->Set(-BLSpeed);
	BRMotor->Set(BRSpeed / 1.02);
}

void MecanumDrive::AutonTurn(float Speed) {
	float driveX = 0;
	float driveY = 0;
	float twist = Speed;

	FLSpeed = driveX + driveY + twist;
	FRSpeed = -driveX + driveY - twist;
	BLSpeed = -driveX + driveY + twist;
	BRSpeed = driveX + driveY - twist;

	double Max = 0;

	if (fabs(FLSpeed) > Max) {
		Max = fabs(FLSpeed);
	}
	if (fabs(FRSpeed) > Max) {
		Max = fabs(FRSpeed);
	}
	if (fabs(BLSpeed) > Max) {
		Max = fabs(BLSpeed);
	}
	if (fabs(BRSpeed) > Max) {
		Max = fabs(BRSpeed);
	}
	if (Max > 1.0) {
		FLSpeed = FLSpeed / Max;
		FRSpeed = FRSpeed / Max;
		BLSpeed = BLSpeed / Max;
		BRSpeed = BRSpeed / Max;
	}

	FLMotor->Set(-FLSpeed);
	FRMotor->Set(FRSpeed / 1.02);
	BLMotor->Set(-BLSpeed);
	BRMotor->Set(BRSpeed / 1.02);
}

void MecanumDrive::SetZero(void) {
	FLMotor->Set(0);
	FRMotor->Set(0);
	BLMotor->Set(0);
	BRMotor->Set(0);
}

void MecanumDrive::ResetEncoders(void) {
	FLMotor->SetPosition(0);
	FRMotor->SetPosition(0);
	BLMotor->SetPosition(0);
	BRMotor->SetPosition(0);
}
