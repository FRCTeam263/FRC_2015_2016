/*
 * ElevatorSpeedAlgorithm.h
 *
 *  Created on: Jan 23, 2015
 *      Author: James
 */

#ifndef ELEVATORSPEEDALGORITHM_H_
#define ELEVATORSPEEDALGORITHM_H_

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

public:
//	ElevatorSpeedAlgorithm();
	ElevatorSpeedAlgorithm(const float theMinVelocityInPercentThatOvercomesMotorInertia = 0.15,
						   float theAccelerationStepSizeInPercent = 0.025,
						   int theDeadbandInEncoderCounts = 50,
						   float theMaxSpeedUpwardInPercent = 0.8,
						   float theMaxSpeedDownwardInPercent = 0.4,
						   float theDelayBetweeenSpeedEvaluationsInSeconds = 0.025,
						   float theSlowBandMultiplier = 3,
						   float theSpeedDownDivisor = 2);
	virtual ~ElevatorSpeedAlgorithm();
	float ComputeNextMotorSpeedCommand(int currentEncoderCount,	int targetEncoderCount);

};

#endif /* ELEVATORSPEEDALGORITHM_H_ */
