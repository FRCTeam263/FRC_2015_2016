package org.usfirst.frc.team263.robot;

import edu.wpi.first.wpilibj.CANTalon;
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.Victor;

public class PDArm implements PDController {
	private double minVelocityInPercentThatOvercomesMotorIntertia = 0.1;
	private double loopTime = .025;
	private double Kp, Kd, distance;
	private CANTalon motor;
	private Encoder enc;
	
	public PDArm(double p, double d, double a, CANTalon m, Encoder e) {
		Kp = p;
		Kd = d;
		// 25/9 is conversion from degrees to motor ticks out of 1000
		// If encoder is a 1500 tick one, use 25/6 instead
		distance = a * 25 / 9;
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
		double p, d, sum;
		while (Math.abs(e) > 10) {
			e = distance - enc.getRaw();
			p = getPTerm(e);
			d = getDTerm(prevE, e);
			sum = -(p+d);
			if (sum < -1.0) {
				sum = -1.0;
				motor.set(-1.0);
			} else if (sum > 1.0) {
				sum = 1.0;
				motor.set(1.0);
			} else {
				motor.set(mapToEffectiveRange(sum));
			}
			System.out.println(sum + " " + enc.getRaw());
			prevE = e;
			Timer.delay(loopTime);
		}
		motor.set(0);
	}
	
	/**
	 * Sets new angle
	 * @param a Angle to go to (degrees)
	 */
	public void setDistance(double a) {
		distance = a * (25/9);
	}
	
	/**
	 * 
	 * @param speed Desired speed in percent
	 * @return Speed mapped to motor's effective range
	 */
	private double mapToEffectiveRange(double speed) {
		int negMult = speed < 0 ? -1 : 1;
		return speed == 0 ? 0 : ((1.0 - minVelocityInPercentThatOvercomesMotorIntertia) * (speed) + minVelocityInPercentThatOvercomesMotorIntertia) * negMult;
	}
	
	/**
	 * Gets proportional term in PD Controller
	 * @param e Current error
	 * @return Proportional term
	 */
	private double getPTerm(double e) {
		// Pout = Kp * e
		return Kp * e / 100;
	}
	
	
	/**
	 * Gets derivative term in PD Controller
	 * @param prevE Error of previous iteration
	 * @param e Current error
	 * @return Derivative term
	 */
	private double getDTerm(double prevE, double e) {
		// Dout = (de(t)/dt) * Kd
		// This is the same as Kd * deltae in this case
		return Kd * (e - prevE) / 100;
	}
}
