package org.usfirst.frc.team263.robot;

import edu.wpi.first.wpilibj.SampleRobot;
import edu.wpi.first.wpilibj.CameraServer;
import edu.wpi.first.wpilibj.Joystick;

public class Robot extends SampleRobot {
    Joystick DrivePad;
    SixWD Drive;
    CameraServer server1;
    CameraServer server2;
    public Robot() {
        DrivePad = new Joystick(0);
        Drive = new SixWD();
        
        server1 = CameraServer.getInstance();
        server1.setQuality(50);
        server1.startAutomaticCapture("cam0");
        
        server2 = CameraServer.getInstance();
        server2.setQuality(50);
        server2.startAutomaticCapture("cam1");
    }

 
    public void autonomous() {
  
    }
    public void operatorControl() {
        while (isOperatorControl() && isEnabled()) {
        	Drive.Drive(DrivePad);
        }
    }

    public void test() {
    }
}
