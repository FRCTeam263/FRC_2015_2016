/*
 * CanGrabber.h
 *
 *  Created on: Jan 10, 2015
 *      Author: Administrator
 */

#ifndef OMEGAX_SRC_SYSTEMS_CANGRABBER_H_
#define OMEGAX_SRC_SYSTEMS_CANGRABBER_H_

#include "WPILib.h"

class CanGrabber {
public:
	CanGrabber();
	~CanGrabber();

	void Extend(Joystick *gamePad);

private:
	Victor *grabber;
	DoubleSolenoid *canExtend;
};

#endif /* OMEGAX_SRC_SYSTEMS_CANGRABBER_H_ */
