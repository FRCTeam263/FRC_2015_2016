package org.usfirst.frc.team263.robot;

import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.Joystick;

public class SixWD {
  private Talon LeftSide,LeftSide2,RightSide,RightSide2;
	public SixWD()
	{
		LeftSide = new Talon(1);
		LeftSide2 = new Talon(3);
		RightSide = new Talon(2);
		RightSide2 = new Talon(0);
		
		LeftSide.set(0);
		RightSide.set(0);
	}
	
	public void Drive(Joystick drivePad)
	{
		double LeftSpeed = drivePad.getRawAxis(1) * -1;
		double RightSpeed = drivePad.getRawAxis(3);

		//float LeftSpeed = drivePad->GetRawAxis(1);
		//float RightSpeed = drivePad->GetRawAxis(3) * -1; //This is assuming you have a
		//logitech controller with 2 analog sticks, one stick for each side.

		if(fabs(LeftSpeed) < 0.2){
			LeftSpeed = 0;
		}
		if(fabs(RightSpeed) <0.2){//sets deadband values so you have to move the
			RightSpeed = 0;// analog stick to a value higher than 0.2/-0.2 for the robot to move.
		}

		LeftSide.set(LeftSpeed);
		LeftSide2.set(LeftSpeed);
		RightSide.set(RightSpeed);
		RightSide2.set(RightSpeed); 	
	}

	private double fabs(double val) {
		if(val < 0)
		{
			val = val * -1;
		}
		return val;
	}
	
	
}



/*
	float LeftSpeed = drivePad->GetRawAxis(1) * -1;
	float RightSpeed = drivePad->GetRawAxis(3);
	//float LeftSpeed = drivePad->GetRawAxis(1);
	//float RightSpeed = drivePad->GetRawAxis(3) * -1; //This is assuming you have a
	//logitech controller with 2 analog sticks, one stick for each side.
	if(fabs(LeftSpeed) < 0.2){
		LeftSpeed = 0;
	}
	if(fabs(RightSpeed) <0.2){//sets deadband values so you have to move the
		RightSpeed = 0;// analog stick to a value higher than 0.2/-0.2 for the robot to move.
	}
	LeftSide->Set(LeftSpeed);
	LeftSide2->Set(LeftSpeed);
	RightSide->Set(RightSpeed);
	RightSide2->Set(RightSpeed); 	
}
 */
