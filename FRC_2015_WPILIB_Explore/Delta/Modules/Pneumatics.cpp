#include "Pneumatics.h"
#include "../Globals.h"

extern Joystick *twistStick;

Pneumatics::Pneumatics(void){
	//compressor = new Compressor(1,1);
	
	shooterPiston = new Solenoid(1);
	//compressor->Start();
}

Pneumatics::~Pneumatics(void){
	
}

void Pneumatics::FirePiston(){	
	shooterPiston->Set(true);
	
	if(twistStick->GetRawButton(9)){
		shooterPiston->Set(true);
	}
	
	/*shooterPiston->Set(false);
	if(twistStick->GetRawButton(1)){
		shooterPiston->Set(true);
	}*/
	//(twistStick->GetRawButton(1)) ? shooterPiston->Set(true) : shooterPiston->Set(false);
}
