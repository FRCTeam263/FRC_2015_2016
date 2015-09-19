/*
 * ElevatorSpeedAlgorithm.h
 *
 *  Created on: Jan 23, 2015
 *      Author: James
 */

#ifndef ELEVATORSPEEDALGORITHM_H_
#define ELEVATORSPEEDALGORITHM_H_

class ElevatorSpeedAlgorithm {
	const float minVelocityInPercentThatOvercomesMotorInertia = 0.25;  // must be determined by empirical measurement.
	const float accelerationStepSizeInPercent = 0.05;  // Increment used to adjust velocity per per time unit.
	const int deadbandInEncoderCounts = 100;  // Arrive "close enough".  Specify [0..n] to affect range of [-n .. n]
	float currentVelocityCommandInPercent = 0;  // range -1.0 .. 1.0
	int encoderCountAtLastEvaluationTimestamp = 0; // used to compute actual velocity of current time interval.
	bool firstTimeCalled = true;

public:
	ElevatorSpeedAlgorithm();
	virtual ~ElevatorSpeedAlgorithm();
	float ComputeNextMotorSpeedCommand(int currentEncoderCount,	int targetEncoderCount);
};

#endif /* ELEVATORSPEEDALGORITHM_H_ */
