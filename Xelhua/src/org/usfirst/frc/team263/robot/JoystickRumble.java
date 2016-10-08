package org.usfirst.frc.team263.robot;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Joystick.RumbleType;
import edu.wpi.first.wpilibj.Timer;

/** 
 * Creates a Thread to vibrate joystick
 * @author Dan Waxman
 * @since 2014-02-14
 * @version 1.0
 */
public class JoystickRumble extends Thread {
	private double duration;
	Joystick drivepad;
	int amount;
	
	/**
	 * @param stick Joystick to rumble
	 * @param occurence Amount of times to rumble
	 */
	public JoystickRumble(Joystick stick, int occurence) {
		duration = 0.25;
		drivepad = stick;
		amount = occurence;
	}
	
	/**
	 * @param stick Joystick to rumble
	 * @param occurence Amount of times to rumble
	 * @param length Duration of rumble
	 */
	public JoystickRumble(Joystick stick, int occurence, double length) {
		duration = length;
		drivepad = stick;
		amount = occurence;
	}
	
	/**
	 * Starts thread where Joystick will rumble
	 */
	@Override
	public void run() {
		for (int i = 0; i < amount; i++) {
			drivepad.setRumble(RumbleType.kLeftRumble, 1f);
			drivepad.setRumble(RumbleType.kRightRumble, 1f);
			
			Timer.delay(duration);
			
			drivepad.setRumble(RumbleType.kLeftRumble, 0f);
			drivepad.setRumble(RumbleType.kRightRumble, 0f);
			
			Timer.delay(0.15);
		}
	}
	
}
