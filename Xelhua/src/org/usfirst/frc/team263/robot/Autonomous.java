package org.usfirst.frc.team263.robot;

import edu.wpi.first.wpilibj.CANTalon;
import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.Talon;

/**
 * Class to control autonomous phase
 * @author Dan Waxman
 * @version 1.3
 * @since 2016-02-18
 */
public class Autonomous {
	private DigitalInput ones;
	private DigitalInput twos;
	private DigitalInput fours;
	private int phase;
	
	/**
	 * Allocates ports for DIO phase detection
	 */
	public Autonomous() {
		ones = new DigitalInput(7);
		twos = new DigitalInput(8);
		fours = new DigitalInput(9);
	}
	
	/**
	 * Detects what autonomous routine to run.
	 * This is done with 7 switches and a binary conversion circuit.
	 */
	public void detectPhase() {
		int sum = 0;
		if (!ones.get()) sum += 1;
		if (!twos.get()) sum += 2;
		if (!fours.get()) sum += 4;
		System.out.println(sum);
		phase = sum;
	}
	
	/**
	 * Drives the autonomous phase selected.
	 * Utilizes the <code>Presets</code> class.
	 */
	public void autoDrive() {
		Talon lf = DriveControls.getLeftFront();
		Talon lb = DriveControls.getLeftBack();
		Talon rf = DriveControls.getRightFront();
		CANTalon rb = DriveControls.getRightBack();
		CANTalon arm = MechanicalControls.getMotorInstance();
		switch (phase) {
		case 1:
			Presets.drawBridge(lf, lb, rf, rb, arm);
			break;
		case 2:
			Presets.portcullis(lf, lb, rf, rb, arm);
			break;
		case 3:
			Presets.cheval(lf, lb, rf, rb, arm);
			break;
		case 4:
			Presets.sallyPort(lf, lb, rf, rb, arm);
			break;
		case 5:
			Presets.ramparts(lf, lb, rf, rb);
			break;
		case 6:
			Presets.moat(lf, lb, rf, rb);
			break;
		case 7:
			Presets.lowBar(lf, lb, rf, rb, arm);
		}
	}
}
