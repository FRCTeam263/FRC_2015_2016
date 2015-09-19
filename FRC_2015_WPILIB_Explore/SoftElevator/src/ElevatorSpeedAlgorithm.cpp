/*
 * ElevatorSpeedAlgorithm.cpp
 *
 *  Created on: Jan 23, 2015
 *      Author: James
 */

#include "ElevatorSpeedAlgorithm.h"
#include <cmath>

ElevatorSpeedAlgorithm::ElevatorSpeedAlgorithm() {
	// TODO Auto-generated constructor stub

}

ElevatorSpeedAlgorithm::~ElevatorSpeedAlgorithm() {
	// TODO Auto-generated destructor stub
}

// Return [-1.0 .. 1.0] to command motor.
float ElevatorSpeedAlgorithm::ComputeNextMotorSpeedCommand(
	int currentEncoderCount,
	int targetEncoderCount )
{
	if (firstTimeCalled)
	{
		firstTimeCalled = false;
		// have to allow lastEncoderCount to be initialized with real measurement at first call for time n-1.
	}
	else
	{
		int measuredVelocityInEncoderCounts = currentEncoderCount - lastEncoderCount;
		int remainingEncoderCountsToTarget = targetEncoderCount - currentEncoderCount;

		if ( fabs(remainingEncoderCountsToTarget) > deadbandInEncoderCounts) {

			// Check current speed against how many more counts remain to go, be sure to
			// provide (add) room for ramp down.  The current velocity times the number of steps it will
			// take to ramp down to zero would be the distance as if we stayed constant at that velocity.
			// Simply divide by two to account for the ramp, results in the total distance travelled during
			// the ramp down.  Thus V * (V/steps) / 2.
			float roomForRampDownInEncoderCounts =
					fabs(measuredVelocityInEncoderCounts) *
				(fabs(measuredVelocityInEncoderCounts) / accelerationStepSizeInPercent + 1) / 2;
			// compare room required to room remaining
			if ( (fabs(measuredVelocityInEncoderCounts) + roomForRampDownInEncoderCounts) <
					fabs(remainingEncoderCountsToTarget) ) {

				// Speed up.  If at zero, jump to get motor past its inertial threshold, then
				// thereafter incrementally ramp velocity up.
				if (currentVelocityCommandInPercent < minVelocityInPercentThatOvercomesMotorInertia)
					currentVelocityCommandInPercent = minVelocityInPercentThatOvercomesMotorInertia;
				else
					currentVelocityCommandInPercent +=
						((remainingEncoderCountsToTarget > 0) ? 1 : -1) * accelerationStepSizeInPercent;
			}
			else {
				// Not enough runway to continue at this velocity, must slow down.  Keep
				// slowing down until reach inertial threshold of motor, then just drop to
				// zero since the motor stopped spinning anyway.  (Threshold handle later)
				currentVelocityCommandInPercent -=
					((remainingEncoderCountsToTarget > 0) ? 1 : -1) * accelerationStepSizeInPercent;
			}
		}
		else {
			currentVelocityCommandInPercent = 0;
		}

		// Keep motor command within motor range -1.0 .. 1.0
		// If within deadband, snap it to zero.
		if (currentVelocityCommandInPercent > 1.0)
			currentVelocityCommandInPercent = 1.0;
		else if (currentVelocityCommandInPercent < -1.0)
			currentVelocityCommandInPercent = -1.0;
		else if (fabs(currentVelocityCommandInPercent) < minVelocityInPercentThatOvercomesMotorInertia)
			currentVelocityCommandInPercent = 0.0;
	}

	// Remember current encoder count and current motor command for next iteration.
	lastEncoderCount = currentEncoderCount;
	return currentVelocityCommandInPercent;
}
