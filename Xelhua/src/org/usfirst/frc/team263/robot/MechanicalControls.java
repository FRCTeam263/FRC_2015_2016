package org.usfirst.frc.team263.robot;

import edu.wpi.first.wpilibj.AnalogPotentiometer;
import edu.wpi.first.wpilibj.CANTalon;
import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.Joystick;

/**
 * Class to control mechanisms other than drivebase
 * @author Dan Waxman
 * @author Rohan Bapat
 * @author Tyler Machado
 * @since 2016-02-01
 * @version 1.3
 */
public class MechanicalControls {
	private boolean alertedEndGame;
	private boolean latchB = false;
	static CANTalon ballGrabberPivot;
	CANTalon ballSpinner;
	CANTalon winch;
	CANTalon latch;
	DigitalInput button;
	private final int A_BUTTON = 1;
	private final int B_BUTTON = 2;
	private final int X_BUTTON = 3;
	private final int Y_BUTTON = 4;
	private DigitalInput ballGrabberLS = new DigitalInput(3);
	private boolean ballInAlerted = false;
	private boolean ballOutAlerted = true;
	private Joystick gamepad;
	private JoystickRumble JRumble;
	private boolean locked = false;
	private boolean lsNotNotified = true;
	private static AnalogPotentiometer pot;
	private DriverStation ds;
	
	/**
	 * Instantiates MechanicalControls class and allocates ports
	 * @param stick Joystick to use for driving
	 */
	public MechanicalControls(Joystick stick) {
		ds = DriverStation.getInstance();		
		pot = new AnalogPotentiometer(0, 360);
		gamepad = stick;
		JRumble = new JoystickRumble(gamepad, 2);
		button = new DigitalInput(4);
		ballGrabberPivot = new CANTalon(2);
		ballSpinner = new CANTalon(1);
		ballSpinner.enableBrakeMode(true);
		winch = new CANTalon(4);
		latch = new CANTalon(3);
	}
	
	/**
	 * Utilizes the winch, ball mechanism, and gives user feedback
	 */
	public void drive() {
		// Makes the pivot go down at 40% speed
		if (gamepad.getRawButton(A_BUTTON) && pot.get() < 240) {
			ballGrabberPivot.set(-0.4);
		} else if (gamepad.getRawButton(B_BUTTON) && ballGrabberLS.get()) {
			// Makes the pivot go down at 50% speed
			// Unless select, the "turbo button" is pressed
			// Then it's 80%
			ballGrabberPivot.set(gamepad.getRawButton(7) ? 0.8 : 0.5);
		} else {
			ballGrabberPivot.set(0.0);
		}
		
		if (ballGrabberLS.get() && lsNotNotified) {
			lsNotNotified = false;
			JRumble = new JoystickRumble(gamepad, 1);
		} else if (ballGrabberLS.get()) {
			lsNotNotified = true;
		}	
		
		// Ball shoots out if x is held
		// Sucks in if Y is held
		if (gamepad.getRawButton(X_BUTTON)) {
			ballSpinner.set(-1.0);
		} else if (gamepad.getRawButton(Y_BUTTON)) {
			ballSpinner.set(locked ? 0.0 : 0.4);
		} else {
			ballSpinner.set(0.0);
		}
		
		// State mechanism for user feedback
		// Rumbles twice if button is actuated for ball pickup
		// Rumbles once after the button is no longer pressed
		if(!button.get() && !ballInAlerted) {
			JRumble = new JoystickRumble(gamepad, 2);
			JRumble.start();
			ballInAlerted = true;
			ballOutAlerted = false;
			locked = true;
		}
		if (button.get() && !ballOutAlerted) {
			JRumble = new JoystickRumble(gamepad, 1);
			JRumble.start();
			ballOutAlerted = true;
			ballInAlerted = false;
			locked = false;
		}
		
		// "Safety button" for winch
		// Start must be pressed before the winch deploys, otherwise it won't work.
		if (gamepad.getRawButton(8)) {
			latchB = true;
		}
		if (latchB) {
			winch.set(gamepad.getRawAxis(1));
			latch.set(gamepad.getRawAxis(5) * -1);
		}
		
		LEDFeedback(ds.getMatchTime() < 25);
	}
	
	/**
	 * @return Ball grabber pivot speed
	 */
	public double getMotor() {
		return ballGrabberPivot.get();
	}
	
	/**
	 * @return Ball grabber pivot instance
	 */
	public static CANTalon getMotorInstance() {
		return ballGrabberPivot;
	}
	
	/**
	 * @return If the ball grabber pivot is in the "down" state
	 */
	public boolean isDown() {
		return pot.get() > 200;
	}
	
	/**
	 * Feedback method written for interaction between robot and drivers via LED strip
	 * @param end If there's 30 seconds or less in the game
	 */
	public void LEDFeedback(boolean end) {
		if (!end) {
			if (gamepad.getRawButton(X_BUTTON) && button.get()) {
				LedStrip.setColor(255, 80, 0); // yellow
			} else if (gamepad.getRawButton(Y_BUTTON) && button.get()) {
				LedStrip.setColor(87, 0, 0); // dark red
			} else if (isDown()) {
				LedStrip.setColor(255, 255, 255); // white
			} else {
				LedStrip.setColor(255, 0, 0); // pure red
			}
		}
		if (end) {
			if (!alertedEndGame) {
				JoystickRumble jr = new JoystickRumble(gamepad, 3);
				JoystickRumble jr2 = new JoystickRumble(DriveControls.getStick(), 3);
				jr2.start();
				jr.start();
				alertedEndGame = true;
			}
			if (gamepad.getRawButton(X_BUTTON) && button.get()) {
				LedStrip.setColor(0, 200, 200); // cyan-ish
			} else if (gamepad.getRawButton(Y_BUTTON) && button.get()) {
				LedStrip.setColor(66, 0, 163); // dark purple
			} else if (isDown()) {
				LedStrip.setColor(123, 174, 255); // light blue
			} else {
				LedStrip.setColor(0, 0, 255); // pure blue
			}
			if (ds.getBatteryVoltage() < 8) {
				LedStrip.setColor(139,69,19); // brown out for potential brownout warnings
			}
		}
	}
}
