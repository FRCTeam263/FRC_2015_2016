package org.usfirst.frc.team263.robot;

import java.util.ArrayList;

/**
 * Utility for recording user movement
 * @author Dan Waxman
 * @since 2016-02-16
 * @version 1.0
 */
public class Recorder {
	private ArrayList<Double> leftFront, rightFront, leftBack, rightBack;
	private ArrayList<Double> mech;
	
	public Recorder() {
		leftFront = new ArrayList<Double>();
		rightFront = new ArrayList<Double>();
		leftBack = new ArrayList<Double>();
		rightBack = new ArrayList<Double>();
		mech = new ArrayList<Double>();
	}
	
	/**
	 * Add drive controls to array
	 * @param controls {leftSpeed, rightSpeed}
	 */
	public void addDrive(double[] controls) {
		if (controls.length != 4) {
			throw new IllegalArgumentException("Recorder.addDrive(double[] controls) can only receive an array of length 4");
		}
		leftFront.add(controls[0]);
		leftBack.add(controls[1]);
		rightFront.add(controls[2]);
		rightBack.add(controls[3]);
	}
	
	/**
	 * Add mech control to array
	 * @param control Control speed for arm
	 */
	public void addMech(double control) {
		mech.add(control);
	}
	
	/**
	 * Prints out arrays to screen
	 */
	public void retrieveArrays() {
		System.out.println("Left front controls: " + leftFront.toString());
		System.out.println("Left back controls: " + leftBack.toString());
		System.out.println("Right front controls: " + rightFront.toString());
		System.out.println("Right back controls: " + rightBack.toString());
		System.out.println("Mechanical controls: " + mech.toString());
	}
}
