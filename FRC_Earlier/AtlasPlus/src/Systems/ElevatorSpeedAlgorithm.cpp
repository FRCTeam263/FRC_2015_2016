/*
 * ElevatorSpeedAlgorithm.cpp
 *
 *  Created on: Jan 23, 2015
 *      Author: James
 */
#include "ElevatorSpeedAlgorithm.h"

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

	levelTimer.Start();
}

ElevatorSpeedAlgorithm::~ElevatorSpeedAlgorithm() {
}

// Return [-1.0 .. 1.0] to command motor.
float ElevatorSpeedAlgorithm::ComputeNextMotorSpeedCommand(
		int currentEncoderCount,
		int targetEncoderCount )
{
	int remainingEncoderCountsToDeadbandWidened;

	if (levelTimer.HasPeriodPassed(delayBetweeenSpeedEvaluations) == true) {

		levelTimer.Reset();

		int remainingEncoderCountsToTarget = targetEncoderCount - currentEncoderCount;
		/*printf("T=%d, d=%d, t=%d, r=%d, ", (int) currentTick,
				currentEncoderCount, targetEncoderCount,
				remainingEncoderCountsToTarget);*/
		if (fabs(remainingEncoderCountsToTarget) > deadbandInEncoderCounts) {

			remainingEncoderCountsToDeadbandWidened = (fabs(remainingEncoderCountsToTarget) - (deadbandInEncoderCounts * slowBandMultiplier));
			bool needToRampDown = (remainingEncoderCountsToDeadbandWidened < 0);

			if (needToRampDown) {
				// Reduce speed each iteration until get within deadband.
				currentVelocityCommandInPercent /= speedDownDivisor;
				/*printf("decrease speed vpct= %f, ",
						currentVelocityCommandInPercent);*/
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
				/*printf("increase speed vpct= %f, ",
						currentVelocityCommandInPercent);*/
			}
		} else {
			currentVelocityCommandInPercent = 0;
			//printf("stop, ");
		}
	}

	// Keep motor command within motor range -1.0 .. 1.0 (actually the defined minimum and maximum for up and down)
	// If within deadband, snap it to zero.
	if((targetEncoderCount == 0) && (currentEncoderCount < remainingEncoderCountsToDeadbandWidened)){
		currentVelocityCommandInPercent = -minVelocityInPercentThatOvercomesMotorInertia * 2;
	}

	if (currentVelocityCommandInPercent > maxSpeedUpwardInPercent)
		currentVelocityCommandInPercent = maxSpeedUpwardInPercent;
	else if (currentVelocityCommandInPercent < -maxSpeedDownwardInPercent)
		currentVelocityCommandInPercent = -maxSpeedDownwardInPercent;
	else if (fabs(currentVelocityCommandInPercent)
			< minVelocityInPercentThatOvercomesMotorInertia)
		currentVelocityCommandInPercent = 0.0;
	//printf("final V= %f\n", currentVelocityCommandInPercent);

	// Remember current encoder count and current motor command for next iteration.
	//	encoderCountAtLastEvaluationTimestamp = currentEncoderCount;

	return currentVelocityCommandInPercent;
}

