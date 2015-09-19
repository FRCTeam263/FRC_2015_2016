#ifndef PNEUMATICS_H_
#define PNEUMATICS_H_

#include "Compressor.h"
#include "Solenoid.h"
#include "../Defines.h"
#include "../Globals.h"

class Pneumatics{
public:
	Pneumatics(void);
	~Pneumatics(void);
	
	void FirePiston(void);
private:
	Compressor *compressor;
	Solenoid *shooterPiston;
	
};

#endif
