package org.usfirst.frc.team263.robot;

public interface PDController {
	public double getKp();
	public double getKd();
	public void setKp(double k);
	public void setKd(double k);
	public void loop();
}
