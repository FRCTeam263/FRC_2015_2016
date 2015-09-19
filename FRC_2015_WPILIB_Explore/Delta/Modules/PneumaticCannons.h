#ifndef PNEUMATICS_CANNONS_H_
#define PNEUMATICS_CANNONS_H_
#include "WPILib.h"
#include "../Defines.h"
#include "MechanumDrive.h"

class PneumaticCannons{
	
public:
	PneumaticCannons();
	~PneumaticCannons();
	void setOuput();	
private:
	Solenoid *leftCannon;
	Solenoid *rightCannon;
};
#endif
