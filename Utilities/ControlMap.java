package org.usfirst.frc.team263.robot;

public class ControlMap {
	// A bunch of global variables for the identity of each button
	private int RIGHT_ANALOG_X, 
				RIGHT_ANALOG_Y,
				LEFT_ANALOG_X,
				LEFT_ANALOG_Y,
				A_BUTTON,
				B_BUTTON,
				X_BUTTON,
				Y_BUTTON,
				LEFT_TRIGGER,
				RIGHT_TRIGGER,
				LEFT_BUMPER,
				RIGHT_BUMPER;
	// Trigger type is 'b' if button or 'a' if axes
	private char TRIGGER_TYPE;
	
	public ControlMap(String s) {
		// Xbox controller controls
		if (s.equals("Controller (Afterglow Gamepad for Xbox 360)")) {
			LEFT_ANALOG_X = 0;
			LEFT_ANALOG_Y = 1;
			RIGHT_ANALOG_X = 4;
			RIGHT_ANALOG_Y = 5;
			A_BUTTON = 1;
			B_BUTTON = 2;
			X_BUTTON = 3;
			Y_BUTTON = 4;
			LEFT_TRIGGER = 2;
			RIGHT_TRIGGER = 3;
			TRIGGER_TYPE = 'a';
			LEFT_BUMPER = 5;
			RIGHT_BUMPER = 6;	
		} else { // Otherwise, only other controller is Logitech
			LEFT_ANALOG_X = 0;
			LEFT_ANALOG_Y = 1;
			RIGHT_ANALOG_X = 2;
			RIGHT_ANALOG_Y = 3;
			A_BUTTON = 2;
			B_BUTTON = 3;
			Y_BUTTON = 4;
			X_BUTTON = 1;
			LEFT_TRIGGER = 7;
			RIGHT_TRIGGER = 8;
			TRIGGER_TYPE = 'b';
			LEFT_BUMPER = 5;
			RIGHT_BUMPER = 6;
		}
	}
	
	// Series of getter methods for each stick/button
	public int getLAnalogX() {
		return LEFT_ANALOG_X;
	}
	public int getLAnalogY() {
		return LEFT_ANALOG_Y;
	}
	public int getRAnalaogX() {
		return RIGHT_ANALOG_X;
	}
	public int getRAnalogY() {
		return RIGHT_ANALOG_Y;
	}
	public int getAButton() {
		return A_BUTTON;
	}
	public int getBButton() {
		return B_BUTTON;
	}
	public int getXButton() {
		return X_BUTTON;
	}
	public int getYButton() {
		return Y_BUTTON;
	}
	public int getLTrigger() {
		return LEFT_TRIGGER;
	}
	public int getRTrigger() {
		return RIGHT_TRIGGER;
	}
	public char getTriggerType() {
		return TRIGGER_TYPE;
	}
	public int getLBumper() {
		return LEFT_BUMPER;
	}
	public int getRBumper() {
		return RIGHT_BUMPER;
	}
}
