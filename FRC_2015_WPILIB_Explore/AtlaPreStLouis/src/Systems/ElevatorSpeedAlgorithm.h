/*
 * ElevatorSpeedAlgorithm.h
 *
 *  Created on: Jan 23, 2015
 *      Author: James
 */
#ifndef ELEVATORSPEEDALGORITHM_H_
#define ELEVATORSPEEDALGORITHM_H_

#include "Timer.h"
#include <cmath>
#include <time.h>

class ElevatorSpeedAlgorithm {
	float minVelocityInPercentThatOvercomesMotorInertia;   // must be determined by empirical measurement.
		float accelerationStepSizeInPercent;  // Increment used to adjust velocity per per time unit.
	    int deadbandInEncoderCounts;  // Arrive "close enough".  Specify [0..n] to affect range of [-n .. n]
	    float maxSpeedUpwardInPercent;
	    float maxSpeedDownwardInPercent;
	    float delayBetweeenSpeedEvaluations;
		float currentVelocityCommandInPercent = 0;  // range -1.0 .. 1.0
		float slowBandMultiplier;
		float speedDownDivisor;
		bool firstTimeCalled = true;

		Timer levelTimer;

public:
	ElevatorSpeedAlgorithm(const float theMinVelocityInPercentThatOvercomesMotorInertia = 0.15,
						   float theAccelerationStepSizeInPercent = 0.01,
						   int theDeadbandInEncoderCounts = 25,
						   float theMaxSpeedUpwardInPercent = 1,
						   float theMaxSpeedDownwardInPercent = 0.5,
						   float delayBetweeenSpeedEvaluations = 0.005,
						   float theSlowBandMultiplier = 5,
						   float theSpeedDownDivisor = 5);
	virtual ~ElevatorSpeedAlgorithm();
	float ComputeNextMotorSpeedCommand(int currentEncoderCount,	int targetEncoderCount);

};

#endif /* ELEVATORSPEEDALGORITHM_H_ */
