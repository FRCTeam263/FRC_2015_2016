package org.usfirst.frc.team263.robot;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Servo;
import edu.wpi.first.wpilibj.Timer;

public class ServoCam {
	Joystick joy1,joy2;
	public ServoCam(Joystick Joy1, Joystick Joy2)
	{
		joy1 = Joy1;
		joy2 = Joy2;
	}
	
	public void RunServos(Servo serElevation, Servo serAzimuth)
	{
		double serE = serElevation.getAngle();
		if (joy1.getPOV() == 0 || joy2.getPOV() == 0) {
			serElevation.setAngle(serE + 10);
			Timer.delay(0.25);
		}
		if (joy1.getPOV() == 180 || joy2.getPOV() == 180) {
			serElevation.setAngle(serE - 10);
			Timer.delay(0.25);
		}
		double serA = serAzimuth.getAngle();
		if (joy1.getPOV() == 90 || joy2.getPOV() == 90) {
			serAzimuth.setAngle(serA + 10);
			Timer.delay(0.25);
		}
		if (joy1.getPOV() == 270 || joy2.getPOV() == 270) {
			serAzimuth.setAngle(serA - 10);
			Timer.delay(0.25);
		}
		if (joy1.getRawButton(5) || joy2.getRawButton(5)) {
			serElevation.setAngle(90);
			Timer.delay(0.25);
		}
		if (joy1.getRawButton(6) || joy2.getRawButton(6)) {
			serAzimuth.setAngle(90);
			Timer.delay(0.25);
		}
	/*	if (serA == 180 || serA == 0 || serE == 180 || serE <= 60){
			joy1.setRumble(Joystick.RumbleType.kLeftRumble, 44);
			joy1.setRumble(Joystick.RumbleType.kRightRumble, 44);
			joy2.setRumble(Joystick.RumbleType.kLeftRumble, 44);
			joy2.setRumble(Joystick.RumbleType.kRightRumble, 44);
		}*/

	}
	
	public void CheckDPad()
	{
		System.out.println(joy1.getPOV());
		Timer.delay(0.1);
	}
}
