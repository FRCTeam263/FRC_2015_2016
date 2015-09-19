#include "BallPickup.h"

extern Joystick *gamePad;

BallPickup::BallPickup(void){
	pickupMotor = new Relay(PICKUP_MOTOR);
	PickupPiston = new DoubleSolenoid(PICKUP_PISTON_1, PICKUP_PISTON_2);
	RobotCompressor = new Compressor(COMPRESSOR, PRESSURE_SWTICH);
	
	pickupMotor->Set(Relay::kOff);
	PickupPiston->Set(DoubleSolenoid::kOff);
	RobotCompressor->Start();
}

BallPickup::~BallPickup(void){
	delete pickupMotor;
	delete PickupPiston;
	delete RobotCompressor;
}
void BallPickup::Pickup(void){ 
	if(gamePad->GetRawButton(2)){
		
		PickupPiston->Set(DoubleSolenoid::kForward);
	}
	else if(gamePad->GetRawButton(3)){
		PickupPiston->Set(DoubleSolenoid::kReverse);
	}
	else{
		PickupPiston->Set(DoubleSolenoid::kOff);
	}
	if(gamePad->GetRawButton(1)){
		pickupMotor->Set(Relay::kForward);
	}
	else if(gamePad->GetRawButton(4)){
		pickupMotor->Set(Relay::kReverse);
	}
	else{
		pickupMotor->Set(Relay::kOff);
	}
}

void BallPickup::AutonBallEject(){
	pickupMotor->Set(Relay::kReverse);
	PickupPiston->Set(DoubleSolenoid::kForward);
}

void BallPickup::AutonPickup(void){
	pickupMotor->Set(Relay::kReverse);
	PickupPiston->Set(DoubleSolenoid::kReverse);
}

void BallPickup::StopPickup(void){
	pickupMotor->Set(Relay::kOff);
	PickupPiston->Set(DoubleSolenoid::kOff);
}
