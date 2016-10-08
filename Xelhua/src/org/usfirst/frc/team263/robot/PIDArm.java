package org.usfirst.frc.team263.robot;

import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.Timer;

public class PIDArm implements PDController {
	private double loopTime = 0.1;
	private double Kp, Kd, distance;
	private Talon motor;
	private Encoder enc;
	
	public PIDArm(double p, double d, double a, Talon m, Encoder e) {
		Kp = p;
		Kd = d;
		distance = a * (25/9);
		motor = m;
		enc = e;
	}
	
	public double getKp() {
		return Kp;
	}
	
	public double getKd() {
		return Kd;
	}
	
	public void setKp(double k) {
		Kp = k;
	}
	
	public void setKd(double k) {
		Kd = k;
	}
	
	/**
	 * Starts PD Controller loop
	 * <p>
	 * Starts PD Controller loop.
	 * This will continue until the error is within an acceptable range.
	 * The loop will refresh every <code>loopTime</code> seconds.
	 */
	public void loop() {
		double e = distance - enc.getRaw();
		double prevE = distance;
		double p, d;
		while (Math.abs(e) > 10) {
			e = distance - enc.getRaw();
			p = getPTerm(e);
			d = getDTerm(prevE, e);
			motor.set(Math.min(1.0, p+d));
			prevE = e;
			Timer.delay(loopTime);
		}
	}
	
	/**
	 * Gets proportional term in PD Controller
	 * @param e Current error
	 * @return Proportional term
	 */
	private double getPTerm(double e) {
		e /= 100;
		return Kp * e;
	}
	
	/**
	 * Gets derivative term in PD Controller
	 * @param prevE Error of previous iteration
	 * @param e Current error
	 * @return Derivative term
	 */
	private double getDTerm(double prevE, double e) {
		e /= 100;
		return Kd * (e - prevE);
	}
}
