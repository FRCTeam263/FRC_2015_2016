package org.usfirst.frc.team263.robot;

import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.Timer;

public class PIDDrive implements PDController {
	private double Kp, Kd, circum, distance;
	private Talon backLeft, backRight, frontLeft, frontRight;
	private Encoder enc;
	private double loopTime = 0.1;
	
	public PIDDrive(double p, double d, double c, double dist, Talon bl, Talon br, Talon fl, Talon fr, Encoder e) {
		Kp = p;
		Kd = d;
		circum = c;
		distance = (dist / circum) * 1000;
		backLeft = bl;
		backRight = br;
		frontLeft = fl;
		frontRight = fr;
		enc = e;
	}
	
	public void setCircum(double c) {
		circum = c;
	}
	
	public void setRad(double r) {
		circum = 2 * Math.PI * r;
	}
	
	public void setDiam(double d) {
		circum = Math.PI * d;
	}
	
	public void setKd(double k) {
		Kd = k;
	}
	
	public void setKp(double k) {
		Kp = k;
	}
	
	public double getKp() {
		return Kp;
	}
	
	public double getKd() {
		return Kd;
	}
	
	public void setDistance(double d) {
		distance = (d / circum) * 1000;
	}
	
	public double getDistance() {
		return distance;
	}
	
	public void loop() {
		enc.reset();
		double e = distance;
		double prevE = distance;
		double p, d;
		while (Math.abs(e) > 10) {
			e = distance - enc.getRaw();
			p = getPTerm(e);
			d = getDTerm(prevE, e);
			frontLeft.set(Math.min(1.0, p+d));
			frontRight.set(Math.min(1.0, p+d));
			backLeft.set(Math.min(1.0, p+d));
			backRight.set(Math.min(1.0, p+d));
			prevE = e;
			Timer.delay(loopTime);
		}
	}
	
	private double getPTerm(double e) {
		e /= 1000;
		return Kp * e;
	}
	
	private double getDTerm(double prevE, double e) {
		e /= 1000;
		return (e - prevE) * Kd;
	}
}
