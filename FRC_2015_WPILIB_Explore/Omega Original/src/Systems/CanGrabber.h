/*
 * CanGrabber.h
 *
 *  Created on: Jan 10, 2015
 *      Author: Administrator
 */

#ifndef SRC_SYSTEMS_CANGRABBER_H_
#define SRC_SYSTEMS_CANGRABBER_H_

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

#endif /* SRC_SYSTEMS_CANGRABBER_H_ */
