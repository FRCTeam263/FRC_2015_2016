#include "liftsystem.h"


liftmotor::liftmotor(void)
{
	Liftmotor1 = new Victor(1);
}
liftmotor::~liftmotor(void)
{
	delete Liftmotor1;
}
void liftmotor::LiftTote(){
	Liftmotor1->Set(1);
}
