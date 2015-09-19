#ifndef AFTERADXL_H_
#define AFTERADXL_H_

#include "WPILib.h"

#define m_period .01
class Notifier;

class AfterADXL {
public:
	AfterADXL();
	~AfterADXL();
	
	void StartADXL();
	
	ADXL345_I2C *getAccelerometer() { return myAccel; }
	
	float getDistance() { return m_distance; }
	float getVelocity() { return m_velocity; }
	
	void appendDistance(float delta) { m_distance += delta; }
	void appendVelocity(float delta) { m_velocity += delta; }
	
	void ResetDistance() { m_distance = 0; }
	void ResetVelocity() { m_velocity = 0; }
private:
	Notifier *m_accelNotifier;
	float m_distance;
	float m_velocity;
	ADXL345_I2C *myAccel;
	static void GetADXLAcceleration(void *controller);
};

#endif
