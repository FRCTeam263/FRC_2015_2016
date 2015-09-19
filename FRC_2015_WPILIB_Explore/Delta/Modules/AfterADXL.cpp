#include "AfterADXL.h"

AfterADXL::AfterADXL() {
	myAccel = new ADXL345_I2C(1, ADXL345_I2C::kRange_2G);
	m_accelNotifier = new Notifier(AfterADXL::GetADXLAcceleration, this);
	m_distance = 0;
	m_velocity = 0;
}

AfterADXL::~AfterADXL() { 
	m_accelNotifier->Stop();
	delete m_accelNotifier;
}

void AfterADXL::StartADXL() {
	m_accelNotifier->StartPeriodic(m_period);
}

void AfterADXL::GetADXLAcceleration(void* controller) {
	AfterADXL *afterADXL = (AfterADXL*)controller;
	
	float y = afterADXL->getAccelerometer()->GetAcceleration(ADXL345_I2C::kAxis_Y);
	
	float delta = y;
	//if(delta < 0) { delta = delta * -1; }
	if(delta > 0.05)
		afterADXL->appendVelocity(y);
	else 
		afterADXL->ResetVelocity();
	
	afterADXL->appendDistance(afterADXL->getVelocity());
	
	
	//printf("Y: %f Distance: %f\t Velocity: %f\n", y, afterADXL->getDistance(), afterADXL->getVelocity());
}
