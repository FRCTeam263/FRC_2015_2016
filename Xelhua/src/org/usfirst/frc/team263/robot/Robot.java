
package org.usfirst.frc.team263.robot;

import org.usfirst.frc.team263.robot.LedStrip.Colors;

import edu.wpi.first.wpilibj.CameraServer;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.DriverStation.Alliance;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.SampleRobot;
import edu.wpi.first.wpilibj.Timer;

public class Robot extends SampleRobot {
	CameraServer cameraS;
	Joystick drivePad;
	Joystick gamePad;
	DriveControls drive;
	MechanicalControls mech;
	Recorder recorder;
	Autonomous autonomous;
	DriverStation ds;

	public Robot() {
		drivePad = new Joystick(0);
		gamePad = new Joystick(1);
		drive = new DriveControls(drivePad);
		mech = new MechanicalControls(gamePad);
		recorder = new Recorder();
		autonomous = new Autonomous();
		ds = DriverStation.getInstance();
	}

	public void robotInit() {
		if (ds.getAlliance().equals(Alliance.Blue)) {
			LedStrip.setColor(Colors.eBlue);
		} else {
			LedStrip.setColor(Colors.eRed);
		}
		cameraS = CameraServer.getInstance();
		cameraS.startAutomaticCapture("cam4");
		cameraS.setQuality(50);
	}
	
	public void disabled() {
		LedStrip.setColor(Colors.eOrange);
	}

	public void autonomous() {
		if (isAutonomous() && isEnabled()) {
			LedStrip.setColor(Colors.eGreen);
			autonomous.detectPhase();
			autonomous.autoDrive();
		}
	}

	public void operatorControl() {
		while (isOperatorControl() && isEnabled()) {
			drive.drive(); 
			mech.drive();
		}
		LedStrip.setColor(Colors.eOrange);
	}

	public void test() {
		while (isTest() && isEnabled()) {
			drive.drive();
			recorder.addDrive(drive.getMotors());
			mech.drive();
			recorder.addMech(mech.getMotor());
			Timer.delay(0.1);
		}
		recorder.retrieveArrays();
	}
}
