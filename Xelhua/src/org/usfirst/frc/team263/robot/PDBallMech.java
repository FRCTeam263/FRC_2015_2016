package org.usfirst.frc.team263.robot;

import edu.wpi.first.wpilibj.CANTalon;
import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.Timer;

public class PDBallMech {
	double loopTime = 0.025;
	int UP_DISTANCE = 267, DOWN_DISTANCE = 10;
	boolean down = true;
	double kp, kd;
	CANTalon motor;
	Encoder enc;
	DigitalInput limitSwitch;
	
	public PDBallMech(double Kp, double Kd, CANTalon m, Encoder feedback, DigitalInput ls) {
		kp = Kp;
		kd = Kd;
		motor = m;
		enc = feedback;
		limitSwitch = ls;
	}
	
	public void loop() {
		System.out.println("Entering Loop");
		double distance = down ? UP_DISTANCE : DOWN_DISTANCE;
		System.out.println("Distance = " + distance);
		double e = distance - enc.getRaw();
		System.out.println("Error = " + e);
		double prevE = e;
		double p, d, sum;
		int i = 1;
		do {
			System.out.println("Entering loop" + i++);
			e =  distance - enc.getRaw();
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
			System.out.println(sum + " " + enc.getRaw() + " " + e);
			prevE = e;
			Timer.delay(loopTime);
		} while (Math.abs(e) > 10 && !limitSwitch.get());
		motor.set(0);
		System.out.println(0 + " " + enc.getRaw());
		down = !down;
	}

	/**
	 * 
	 * @param speed Desired speed in percent
	 * @return Speed mapped to motor's effective range
	 */
	private double mapToEffectiveRange(double speed) {
		if (speed == 0) return 0;
		if (speed > 0) return (13/20) * (speed) + 0.35;
		return (13/20) * (speed) - 0.35;
	}
	
	/**
	 * Gets proportional term in PD Controller
	 * @param e Current error
	 * @return Proportional term
	 */
	private double getPTerm(double e) {
		// Pout = Kp * e
		return kp * e / 100;
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
		return kd * (e - prevE) / 100;
	}
}
