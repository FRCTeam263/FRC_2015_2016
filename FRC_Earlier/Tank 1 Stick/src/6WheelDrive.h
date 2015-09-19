/*
 * 6WheelDrive.h
 *
 *  Created on: Jan 9, 2015
 *      Author: Tejas Prasad
 */

#ifndef SRC_6WHEELDRIVE_H_
#define SRC_6WHEELDRIVE_H_

#include "WPILib.h"

class SixWD{
public:
	SixWD();
	~SixWD();

	void Drive(Joystick *drivePad);

private:
	Talon *LeftSide;//You can change this from Talon to whichever motor controller you are using.
	Talon *LeftSide2;
	Talon *RightSide;//For example, Victor, TalonSRX, etc.
	Talon *RightSide2;
};

#endif /* SRC_6WHEELDRIVE_H_ */
