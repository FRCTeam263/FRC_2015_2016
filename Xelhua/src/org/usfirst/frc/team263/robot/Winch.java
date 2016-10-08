package org.usfirst.frc.team263.robot;

import edu.wpi.first.wpilibj.CANTalon;
import edu.wpi.first.wpilibj.DoubleSolenoid;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.Timer;

public class Winch {
	CANTalon winchMotor;
	ControlMap map;
	DoubleSolenoid extendArm;

	public Winch() {
		winchMotor = new CANTalon(0);
		extendArm = new DoubleSolenoid(2, 3);
	}

	public void runWinch(Joystick drivePad) {
		// press A extends solenoid
		// holding LT and pressing a again runs motor
		boolean runMotor = false;
		map = new ControlMap(drivePad.getName());
		if (drivePad.getRawButton(map.getAButton())) {
			extendArm.set(DoubleSolenoid.Value.kForward);
			runMotor = true;
		}

		if (drivePad.getRawButton(map.getAButton()) && drivePad.getRawAxis(map.getLTrigger()) != 0 && runMotor) {
			// run motor till bot is all the way up
			// motor run time isnt certain, 2 seconds is temporary
			winchMotor.set(0.5);
			Timer.delay(2);
			winchMotor.set(0.0);
			runMotor = false;
		}
	}
}
