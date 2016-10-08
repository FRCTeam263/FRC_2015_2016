/*
 * ElevatorSpeedAlgorithm.cpp
 *
 *  Created on: Jan 23, 2015
 *      Author: James
 */

#include "WPILib.h"
#include "ElevatorSpeedAlgorithm.h"
#include <cmath>
#include <time.h>

//ElevatorSpeedAlgorithm::ElevatorSpeedAlgorithm() {
//	// TODO Auto-generated constructor stub
//
//}

ElevatorSpeedAlgorithm::ElevatorSpeedAlgorithm(
		const float theMinVelocityInPercentThatOvercomesMotorInertia,
		float theAccelerationStepSizeInPercent, int theDeadbandInEncoderCounts,
		float theMaxSpeedUpwardInPercent, float theMaxSpeedDownwardInPercent,
		float theDelayBetweeenSpeedEvaluations, float theSlowBandMultiplier, float theSpeedDownDivisor) {
	minVelocityInPercentThatOvercomesMotorInertia =
			theMinVelocityInPercentThatOvercomesMotorInertia;
	accelerationStepSizeInPercent = theAccelerationStepSizeInPercent;
	deadbandInEncoderCounts = theDeadbandInEncoderCounts;
	maxSpeedUpwardInPercent = theMaxSpeedUpwardInPercent;
	maxSpeedDownwardInPercent = theMaxSpeedDownwardInPercent;
	delayBetweeenSpeedEvaluations = theDelayBetweeenSpeedEvaluations;
	slowBandMultiplier = theSlowBandMultiplier;
	speedDownDivisor = theSpeedDownDivisor;
}

ElevatorSpeedAlgorithm::~ElevatorSpeedAlgorithm() {
	// TODO Auto-generated destructor stub
}

// Return [-1.0 .. 1.0] to command motor.
float ElevatorSpeedAlgorithm::ComputeNextMotorSpeedCommand(
		int currentEncoderCount, int targetEncoderCount) {
/*const clock_t clockDelayBetweeenSpeedEvaluations =
			delayBetweeenSpeedEvaluations * CLOCKS_PER_SEC;
	static clock_t lastEvaluationTimestamp = clock()
			- clockDelayBetweeenSpeedEvaluations;
	clock_t currentTick = -1;
	currentTick = clock();
	if ((currentTick - lastEvaluationTimestamp)
			>= clockDelayBetweeenSpeedEvaluations) {
		lastEvaluationTimestamp = currentTick;*/
	Timer timer;
	timer.Reset();
	timer.Start();
	if(timer.HasPeriodPassed((double)delayBetweeenSpeedEvaluations))
	{
		int remainingEncoderCountsToTarget = targetEncoderCount
				- currentEncoderCount;
		printf("T=%d, d=%d, t=%d, r=%d, ", timer.Get(),
				currentEncoderCount, targetEncoderCount,
				remainingEncoderCountsToTarget);
		if (fabs(remainingEncoderCountsToTarget) > deadbandInEncoderCounts) {

			int remainingEncoderCountsToDeadbandWidened = (fabs(
					remainingEncoderCountsToTarget)
					- (deadbandInEncoderCounts * slowBandMultiplier));
			bool needToRampDown = (remainingEncoderCountsToDeadbandWidened < 0);

			if (needToRampDown) {
				// Reduce speed each iteration until get within deadband.
				currentVelocityCommandInPercent /= speedDownDivisor;
				printf("decrease speed vpct= %f, ",
						currentVelocityCommandInPercent);
			} else {
				// Speed up.  If at zero, jump to get motor past its inertia threshold, then
				// thereafter incrementally ramp velocity up. Don't worry, later we'll limit it.
				if (fabs(currentVelocityCommandInPercent)
						< minVelocityInPercentThatOvercomesMotorInertia)
					currentVelocityCommandInPercent = (
							(remainingEncoderCountsToTarget > 0) ? 1 : -1)
							* minVelocityInPercentThatOvercomesMotorInertia;
				else
					currentVelocityCommandInPercent += (
							(remainingEncoderCountsToTarget > 0) ? 1 : -1)
							* accelerationStepSizeInPercent;
				printf("increase speed vpct= %f, ",
						currentVelocityCommandInPercent);
			}
		} else {
			currentVelocityCommandInPercent = 0;
			printf("stop, ");
		}
	}

// Keep motor command within motor range -1.0 .. 1.0 (actually the defined minimum and maximum for up and down)
// If within deadband, snap it to zero.
	if (currentVelocityCommandInPercent > maxSpeedUpwardInPercent)
		currentVelocityCommandInPercent = maxSpeedUpwardInPercent;
	else if (currentVelocityCommandInPercent < -maxSpeedDownwardInPercent)
		currentVelocityCommandInPercent = -maxSpeedDownwardInPercent;
	else if (fabs(currentVelocityCommandInPercent)
			< minVelocityInPercentThatOvercomesMotorInertia)
		currentVelocityCommandInPercent = 0.0;
	printf("final V= %f\n", currentVelocityCommandInPercent);

// Remember current encoder count and current motor command for next iteration.
//	encoderCountAtLastEvaluationTimestamp = currentEncoderCount;

	return currentVelocityCommandInPercent;
}
