#ifndef BALLPICKUP_H_
#define BALLPICKUP_H_

#include "Relay.h"
#include "Joystick.h"
#include "DoubleSolenoid.h"
#include "Compressor.h"
#include "../Globals.h"
#include "../Defines.h"
#include "Utilities.h"

class BallPickup{
public:
	BallPickup(void);
	~BallPickup(void);
	
	void Pickup(void);
	void AutonPickup(void);
	void AutonBallEject(void);
	void StopPickup(void);
private:
	Compressor *RobotCompressor;
	Relay *pickupMotor;
	DoubleSolenoid *PickupPiston;
};

#endif
