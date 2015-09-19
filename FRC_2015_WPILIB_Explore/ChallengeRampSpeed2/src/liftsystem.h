/*
 * liftsystem.h
 *
 *  Created on: Jan 6, 2015
 *      Author: Dolan's
 */

#ifndef SRC_LIFTSYSTEM_H_
#define SRC_LIFTSYSTEM_H_

#include "WPILib.h"


class liftmotor
{
public:
	liftmotor(void);
    ~liftmotor(void);

    void LiftTote(Joystick *GameController);
private:
    Victor *Liftmotor1;
};

#endif /* SRC_LIFTSYSTEM_H_ */
