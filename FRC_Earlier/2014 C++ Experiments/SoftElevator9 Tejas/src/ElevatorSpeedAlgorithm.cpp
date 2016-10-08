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
						   float theAccelerationStepSizeInPercent,
						   int theDeadbandInEncoderCounts,
						   float theMaxSpeedUpwardInPercent,
						   float theMaxSpeedDownwardInPercent,
						   float theDelayBetweeenSpeedEvaluations)
{
	minVelocityInPercentThatOvercomesMotorInertia = theMinVelocityInPercentThatOvercomesMotorInertia;
	accelerationStepSizeInPercent = theAccelerationStepSizeInPercent;
	deadbandInEncoderCounts = theDeadbandInEncoderCounts;
	maxSpeedUpwardInPercent = theMaxSpeedUpwardInPercent;
	maxSpeedDownwardInPercent = theMaxSpeedDownwardInPercent;
	delayBetweeenSpeedEvaluations = theDelayBetweeenSpeedEvaluations;
}

ElevatorSpeedAlgorithm::~ElevatorSpeedAlgorithm() {
	// TODO Auto-generated destructor stub
}

// Return [-1.0 .. 1.0] to command motor.
float ElevatorSpeedAlgorithm::ComputeNextMotorSpeedCommand(
	int currentEncoderCount,
	int targetEncoderCount )
{
	const clock_t clockDelayBetweeenSpeedEvaluations = delayBetweeenSpeedEvaluations * CLOCKS_PER_SEC;
	static clock_t lastEvaluationTimestamp = clock() - clockDelayBetweeenSpeedEvaluations;
	static float lastVelocityCommandedInPercent = -1;
	clock_t currentTick = -1;

	if (firstTimeCalled)
	{
		firstTimeCalled = false;
		// have to allow lastEncoderCount to be initialized with real measurement at first call for time n-1.

		// Remember current encoder count and current motor command for next iteration.
		encoderCountAtLastEvaluationTimestamp = currentEncoderCount;
	}
	else
	{
		currentTick = clock();
		if ((currentTick - lastEvaluationTimestamp) > clockDelayBetweeenSpeedEvaluations)
		{
			lastEvaluationTimestamp = currentTick;

			int measuredVelocityInEncoderCounts = currentEncoderCount - encoderCountAtLastEvaluationTimestamp;
			int remainingEncoderCountsToTarget = targetEncoderCount - currentEncoderCount;
			printf("T=%d, d=%d, t=%d, v=%d, r=%d, ",(int)currentTick,currentEncoderCount,targetEncoderCount,measuredVelocityInEncoderCounts,remainingEncoderCountsToTarget);

			if ( fabs(remainingEncoderCountsToTarget) > deadbandInEncoderCounts) {

				// Check current speed against how many more counts remain to go, be sure to
				// provide (add) room for ramp down.  The current velocity times the number of steps it will
				// take to ramp down to zero would be the distance as if we stayed constant at that velocity.
				// Simply divide by two to account for the ramp, results in the total distance travelled during
				// the ramp down.  Thus (Vcounts * (V%/step%)) / 2.  Assume current velocity measured from last
				// iteration is proportional to the last commmanded velocity in percent.
				float numberOfIterationsItWillTakeToStop = fabs(lastVelocityCommandedInPercent/accelerationStepSizeInPercent);
				float roomForRampDownInEncoderCounts =
						fabs(measuredVelocityInEncoderCounts) * numberOfIterationsItWillTakeToStop / 2.0;
//						fabs(measuredVelocityInEncoderCounts) *
//					(fabs(measuredVelocityInEncoderCounts) / (1/accelerationStepSizeInPercent)) / 2; //TODO check into this
				printf("room=%f, ", roomForRampDownInEncoderCounts);
				// compare room required to room remaining.  Anticipate an extra
				// iteration at current speed, and add the ramp down room to it.
				if ( (fabs(measuredVelocityInEncoderCounts) + roomForRampDownInEncoderCounts) <
						fabs(remainingEncoderCountsToTarget) ) {

					// Speed up.  If at zero, jump to get motor past its inertia threshold, then
					// thereafter incrementally ramp velocity up. Don't worry, later we'll limit it.
					if (fabs(currentVelocityCommandInPercent) < minVelocityInPercentThatOvercomesMotorInertia)
						currentVelocityCommandInPercent =((remainingEncoderCountsToTarget > 0) ? 1 : -1) * minVelocityInPercentThatOvercomesMotorInertia;
					else
						currentVelocityCommandInPercent +=
							((remainingEncoderCountsToTarget > 0) ? 1 : -1) * accelerationStepSizeInPercent;
					printf("increase speed vpct= %f, ", currentVelocityCommandInPercent);
				}
				else {
					// Not enough runway to continue at this velocity, must slow down.  Keep
					// slowing down until reach inertial threshold of motor, then just drop to
					// zero since the motor stopped spinning anyway.  (Threshold handle later)
					currentVelocityCommandInPercent -=
						((remainingEncoderCountsToTarget > 0) ? 1 : -1) * accelerationStepSizeInPercent;
					printf("decrease speed vpct= %f, ", currentVelocityCommandInPercent);
				}
			}
			else {
				currentVelocityCommandInPercent = 0;
				printf("stop, ");
			}

			// Keep motor command within motor range -1.0 .. 1.0 (actually the defined minimum and maximum for up and down)
			// If within deadband, snap it to zero.
			if (currentVelocityCommandInPercent > maxSpeedUpwardInPercent)
				currentVelocityCommandInPercent = maxSpeedUpwardInPercent;
			else if (currentVelocityCommandInPercent < -maxSpeedDownwardInPercent)
				currentVelocityCommandInPercent = -maxSpeedDownwardInPercent;
			else if (fabs(currentVelocityCommandInPercent) < minVelocityInPercentThatOvercomesMotorInertia)
				currentVelocityCommandInPercent = 0.0;
			printf("final V= %f\n",currentVelocityCommandInPercent);

			// Remember current encoder count and current motor command for next iteration.
			encoderCountAtLastEvaluationTimestamp = currentEncoderCount;
		}
	}
	if (lastVelocityCommandedInPercent != currentVelocityCommandInPercent )
		printf("Output V = %f\n",currentVelocityCommandInPercent);
	lastVelocityCommandedInPercent = currentVelocityCommandInPercent;
	return currentVelocityCommandInPercent;
}
