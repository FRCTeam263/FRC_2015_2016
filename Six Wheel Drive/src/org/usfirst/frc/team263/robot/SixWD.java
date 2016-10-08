package org.usfirst.frc.team263.robot;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Talon;

public class SixWD {
	/* 
	 * USE XBOX CONTROLLER ONLY
	 * OTHERS WILL NOT WORK CORRECTLY
	 */
	private Talon leftFront, leftBack, rightFront, rightBack;
	private int RIGHT_ANALOG = 4;
	private int LEFT_ANALOG = 1;
	private int LEFT_TRIGGER = 2;
	private int RIGHT_TRIGGER = 3;
	private boolean linear; // True when going forward -- used for turning
	private double leftSpeed = 0, rightSpeed = 0;

	public SixWD() {
		// Assign Talons correct ports
		leftFront = new Talon(1);
		leftBack = new Talon(3);
		rightFront = new Talon(2);
		rightBack = new Talon(0);

		leftFront.set(0);
		rightFront.set(0);
	}

	public void Drive(Joystick drivepad) {
		linear = Math.abs(drivepad.getRawAxis(LEFT_ANALOG)) > 0.1;
		// If the left analog stick is going forwards or backwards
		if (linear) {
			double value = drivepad.getRawAxis(LEFT_ANALOG);
			leftSpeed = value;
			rightSpeed = value;
		} 
		
		// If the robot is moving forwards and the right analog is used to turn
		// We should turn by decreasing the opposite side's motor.
		// This is to keep motor values from going above 1.0
		// If the robot is not going forwards, just assign the turning value as the motor value
		if (linear && Math.abs(drivepad.getRawAxis(RIGHT_ANALOG)) > 0.1) {
			if (drivepad.getRawAxis(RIGHT_ANALOG) > 0) {
				rightSpeed /= (10 * drivepad.getRawAxis(RIGHT_ANALOG)); // Turn to the left
			} else if (drivepad.getRawAxis(RIGHT_ANALOG) < 0) {
				leftSpeed /= (10 * Math.abs(drivepad.getRawAxis(RIGHT_ANALOG))); // Turn to the right
			}
		} else if (Math.abs(drivepad.getRawAxis(RIGHT_ANALOG)) > 0.1) {
			if (drivepad.getRawAxis(RIGHT_ANALOG) > 0) {
				leftSpeed = -drivepad.getRawAxis(RIGHT_ANALOG);
			} else {
				rightSpeed = drivepad.getRawAxis(RIGHT_ANALOG);
			}
		}
		
		// If the robot is not moving fowards or turning, there are three options:
		// (1) left trigger (turn in place left) 
		// (2) right trigger (turn in place right)
		// (3) robot is not moving and motor values should be set to 0
		if (!linear && Math.abs(drivepad.getRawAxis(RIGHT_ANALOG)) <= 0.1) {
			if (drivepad.getRawAxis(LEFT_TRIGGER) > 0.1) { // Turn in place left
				leftSpeed = drivepad.getRawAxis(LEFT_TRIGGER);
				rightSpeed = -drivepad.getRawAxis(LEFT_TRIGGER);
			} else if (drivepad.getRawAxis(RIGHT_TRIGGER) > 0.1) { // Turn in place right
				leftSpeed = -drivepad.getRawAxis(RIGHT_TRIGGER);
				rightSpeed = drivepad.getRawAxis(RIGHT_TRIGGER);
			} else { // Set motors to zero
				leftSpeed = 0;
				rightSpeed = 0;
			}
		}
		// Left motors are set in the wrong direction for some reason, so it has to be set to negative value to work
		leftSpeed *= -1;
		leftFront.set(leftSpeed);
		leftBack.set(leftSpeed);
		rightFront.set(rightSpeed);
		rightBack.set(rightSpeed);
	}
}
