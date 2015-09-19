#include "Autonomous.h"

AutonomousSystem::AutonomousSystem(){
	autoMode = Lift1Tote;
	toteLifterOutput = new ElevatorSpeedAlgorithm();
	canLifterOutput = new ElevatorSpeedAlgorithm(0.3, 0.02, 10, 1, 0.5, 0.005, 5, 5);
	driveOutput = new ElevatorSpeedAlgorithm();
}

AutonomousSystem::~AutonomousSystem(){
	delete toteLifterOutput;
	delete canLifterOutput;
	delete driveOutput;
}

void AutonomousSystem::Run3ToteAuto(MecanumDrive *drive, LiftSystem *lifter){

	float toteLifterDistance = lifter->shortLiftMotor1->GetPosition();
	float WheelEncoder = drive->FLMotor->GetPosition();
	float canLifterDistance = lifter->canLiftMotor->GetPosition();

	float toteLifterSetpoint = 0;
	float canLifterSetpoint = 0;

	if(lifter->shortBottomLS->Get() == true){
		lifter->shortLiftMotor1->SetPosition(0);
	}
	if(lifter->canBottomLS->Get() == true){
		lifter->canLiftMotor->SetPosition(0);
	}

	printf("Tote: %f\t Can: %f\t Wheel: %f\n", toteLifterDistance, canLifterDistance, WheelEncoder);


	switch(autoMode){
	case Reset:
		if(lifter->shortBottomLS->Get() == true && lifter->canBottomLS->Get() == true){
			lifter->shortLiftMotor1->SetPosition(0);
			drive->FLMotor->SetPosition(0);

			toteLifterSetpoint = 0;
			canLifterSetpoint = 0;

			autoMode = Lift1Tote;
		}
		else if(lifter->shortBottomLS->Get() == false){
			toteLifterSetpoint = -1;
		}
		else if(lifter->canBottomLS->Get() == false){
			canLifterSetpoint = -1;
		}
		drive->FLMotor->SetPosition(0);
		drive->FRMotor->SetPosition(0);
		drive->BLMotor->SetPosition(0);
		drive->BRMotor->SetPosition(0);
		break;

	case Lift1Tote:
		if(canLifterDistance < elevatorCanLevels[4]){
			canLifterSetpoint = canLifterOutput->ComputeNextMotorSpeedCommand(canLifterDistance, elevatorCanLevels[4]);
			drive->ResetEncoders();
			printf("canlift");
		}
		else if((canLifterDistance >= elevatorCanLevels[4]) && (WheelEncoder < autonDrive1[1]) && (toteLifterDistance < elevatorShortLevels[2])){

			drive->AutonDriveStraight(false, driveOutput->ComputeNextMotorSpeedCommand(WheelEncoder, autonDrive1[1]) * -1);
			if(WheelEncoder > autonDrive1[1]){
				drive->AutonDriveStraight(false, 0);
			}
			printf("drivefwd");
		}
		else if(canLifterDistance >= elevatorCanLevels[4] && WheelEncoder >= autonDrive1[1] && toteLifterDistance < elevatorShortLevels[2]){

			toteLifterSetpoint = toteLifterOutput->ComputeNextMotorSpeedCommand(toteLifterDistance, elevatorShortLevels[2]);
			printf("lifttote");

		}
		else if((canLifterDistance >= elevatorCanLevels[4]) && (WheelEncoder >= autonDrive1[1]) && (WheelEncoder < autonDrive1[2]) && (toteLifterDistance >= (elevatorShortLevels[2]) - 40)){
			autoMode = Stack1Tote;
			printf("StackEntered");
		}
		else {
			drive->SetZero();
			lifter->SetZero();
		}
		break;

	case Stack1Tote:
		if((WheelEncoder >= autonDrive1[1]) && (WheelEncoder < autonDrive1[2])){
			drive->AutonTurn(-driveOutput->ComputeNextMotorSpeedCommand(WheelEncoder, autonDrive1[2]) / 2);
			if(WheelEncoder >= autonDrive1[2]){
				drive->SetZero();
			}
			printf("turn");
		}
		else if(WheelEncoder >= (autonDrive1[2] - 30) && WheelEncoder < autonDrive1[3]){
			drive->AutonDriveStraight(false, -driveOutput->ComputeNextMotorSpeedCommand(WheelEncoder, autonDrive1[3]) / 3);
			if(WheelEncoder >= autonDrive1[3]){
				drive->SetZero();
			}
			printf("drivefwd2");
		}
		else if(WheelEncoder >= autonDrive1[3] && toteLifterDistance >= elevatorShortLevels[0]){
			toteLifterSetpoint = -1;
			if(lifter->shortBottomLS->Get() == true){
				toteLifterSetpoint = 0;
				drive->ResetEncoders();
				autoMode = Lift2Totes;
				printf("changed");
			}
			printf("stack1tote");
		}
		else{
			lifter->SetZero();
			drive->SetZero();
		}
		break;

	case Lift2Totes:
		if(WheelEncoder < autonDrive2[1]){
			drive->AutonDriveStraight(false, -0.5);
			if(WheelEncoder >= autonDrive2[1]){
				drive->SetZero();
			}
			printf("lineuptotes");
		}
		else if(WheelEncoder >= autonDrive2[1] && toteLifterDistance < elevatorShortLevels[2]){
			toteLifterSetpoint = toteLifterOutput->ComputeNextMotorSpeedCommand(toteLifterDistance, elevatorShortLevels[2]);
			if(toteLifterDistance > elevatorShortLevels[2]){
				toteLifterSetpoint = 0;
			}
			printf("lift2totes");
		}

		/*
		else if((WheelEncoder >= autonDrive[3]) && (WheelEncoder < autonDrive[4]) && toteLifterDistance == 0){
			drive->AutonDriveStraight(false, -driveOutput->ComputeNextMotorSpeedCommand(WheelEncoder, autonDrive[4]));
			printf("linetotes");
		}*/

		/*else if((canLifterDistance >= elevatorCanLevels[4]) && (WheelEncoder > autonDrive[2] && WheelEncoder < autonDrive[3]) && (toteLifterDistance >= elevatorShortLevels[2])){
			drive->AutonDriveStraight(false, driveOutput->ComputeNextMotorSpeedCommand(WheelEncoder, autonDrive[3]));
			if(WheelEncoder > autonDrive[3]){
				drive->SetZero();
			}
		}*/
		/*if(toteLifterDistance <= elevatorShortLevels[1]){//lift tote up
			toteLifterSetpoint = toteLifterOutput->ComputeNextMotorSpeedCommand(toteLifterDistance, elevatorShortLevels[2]);
		}*/

		/*else if((LifterDistance >= elevatorShortLevels[2] && LifterDistance <= elevatorShortLevels[3]) && WheelEncoder <= 100){//rotate left 90. and lift to 1.5 totes high lift > 150, wheel > 100
			drive->AutonTurn(0.5);

			toteLifterSetpoint = elevatorShortLevels[3];
		}

		else if(LifterDistance >= 150 && (WheelEncoder >= 100 && WheelEncoder <= 1000)){//drive Forward x distance to 2nd tote. and set to step 2.
			drive->AutonDriveStraight(true, 0.5);

			toteLifterSetpoint = 0;
		}

		else if(LifterDistance >= 150 && WheelEncoder >= 1000){
			autoMode = Stack1Tote;
		}*/
		else{
			drive->SetZero();
			lifter->SetZero();
		}
		break;
	/*
	case Stack1Tote:

		if(WheelEncoder >= 1000){//when reachs 2nd tote, reset encoder value.
			drive->FLMotor->SetPosition(0);
		}

		else if(LifterDistance >= 150 && WheelEncoder <= 100){//rotate -90 so 1st tote is above 2nd tote
			drive->AutonTurn(-0.5);
		}

		else if(LifterDistance >= 90 && WheelEncoder >= 100){//lowers 1st tote onto 2nd tote
			LifterSetpoint = lifterOutput->ComputeNextMotorSpeedCommand(LifterDistance, elevatorShortLevels[0]);
			drive->FLMotor->SetPosition(0);
		}
//
//		else if(((LifterDistance >= 0 && LifterDistance <= 95) && WheelEncoder >= -20)){//drive back to wheel <= -20 lift <= 0. set mode to step3
//			drive->AutonDriveStraight(true, -0.5);
//
//			if(lifter->shortBottomLS->Get() == false){
//				LifterSetpoint = -1;
//			}
//		}
		else if(LifterDistance == 0 && WheelEncoder <= -20){
			autoMode = Lift2Totes;
		}
		else{
			drive->SetZero();
			lifter->SetZero();
		}
		break;

	case Lift2Totes:

		if(lifter->toteTouchSensor->Get() == false){//drive forward to 2nd tote.
			drive->AutonDriveStraight(true, 0.5);
			drive->FLMotor->SetPosition(0);
		}

		else if(LifterDistance <= elevatorShortLevels[3]){//move totes up
			LifterSetpoint = lifterOutput->ComputeNextMotorSpeedCommand(LifterDistance, elevatorShortLevels[3]);
		}

		else if((LifterDistance >= 110 && LifterDistance <= 160) && WheelEncoder <= 100){//rotate and move totes higher
			drive->AutonTurn(0.5);
		}

		else if(LifterDistance >= 150 && (WheelEncoder >= 100 && WheelEncoder <= 1000)){//move forward to 3rd tote
			drive->AutonDriveStraight(true, 0.5);
		}

		else if(LifterDistance >= 150 && WheelEncoder >= 1000){
			autoMode = Stack2Totes;
		}

		else{
			drive->SetZero();
			lifter->SetZero();
		}
		break;

	case Stack2Totes:

		if(WheelEncoder >= 1000){//when reaches 3rd tote, reset encoder value.
			drive->FLMotor->SetPosition(0);
		}

		else if(LifterDistance >= 150 && WheelEncoder <= 100){//rotate -90 so 1st tote is above 3rd tote
			drive->AutonTurn(-0.5);		}

		else if(LifterDistance >= 90 && WheelEncoder >= 100){//lowers totes onto 3rd tote
			LifterSetpoint = -0.5;
			drive->FLMotor->SetPosition(0);
		}

//		else if(((LifterDistance >= 0 && LifterDistance <= 95) && WheelEncoder >= -20)){//drive back to wheel <= -20 lift <= 0. set mode to step3
//			drive->AutonDriveStraight(true, -0.5);
//
//			if(lifter->canBottomLS->Get() == false){
//				LifterSetpoint = -1;
//			}
//		}
		else if(LifterDistance <= 10 && WheelEncoder <= -20){
			autoMode = Lift3Totes;
		}

		else{
			drive->SetZero();
			lifter->SetZero();
		}
		break;

	case Lift3Totes:

		if(lifter->toteTouchSensor->Get() == false){//drive forward to tote stack.
			drive->AutonDriveStraight(true, 0.5);
			drive->FLMotor->SetPosition(0);
		}

		else if(LifterDistance <= 110){//move totes up
			LifterSetpoint = 0.5;
		}

		else if(WheelEncoder >= -200){
			drive->AutonDriveStraight(true, -0.5);
		}
		else if(WheelEncoder <= -200 && (LifterDistance >= 0 && lifter->canBottomLS->Get() == false)){
			LifterSetpoint = -0.5;
		}

		else if(WheelEncoder <= -200 && lifter->canBottomLS->Get()){
			autoMode = DriveToAutoZone;
		}

		else{
			drive->SetZero();
			lifter->SetZero();
		}
		break;
	case DriveToAutoZone:
		if( lifter->canBottomLS->Get() && WheelEncoder >= -300){
			drive->AutonDriveStraight(true, -1);
		}

		else{
			drive->SetZero();
			lifter->SetZero();
		}
		break;*/
	}

	lifter->SetToteSpeed(toteLifterSetpoint);
	lifter->SetCanSpeed(canLifterSetpoint);
}

void AutonomousSystem::RunNothing(MecanumDrive *drive, LiftSystem *lifter){
	drive->SetZero();
	lifter->SetZero();
}
