package org.usfirst.frc.team263.robot;

import java.util.ArrayList;

import edu.wpi.first.wpilibj.I2C;
import edu.wpi.first.wpilibj.Joystick;

/**
 * Class for communicating with arduino on i2c bus for LED communication
 * @author Rohan Bapat
 * @version 2.1
 * @since 2015-12-15
 */
public class LedStrip {
	private static final int i2cAddress_Arduino = 10;
	static I2C i2c = new I2C(I2C.Port.kOnboard, i2cAddress_Arduino);
	static ArrayList<int[]> ColorList = new ArrayList<>();
	static boolean valuesLogged = false;

	public static enum Colors {
		eRed, eGreen, eBlue, ePink, ePurple, eOrange, eWhite, eTeal,
	}

	//send r,g,and b values to arduino
	public static void setColor(int red, int green, int blue) {
		int colors[] = new int[] { red, green, blue };
		for (int i : colors) {
			byte byteArray[] = { (byte) i };
			if (i2c.writeBulk(byteArray)) {
			} else {
			}
			// Timer.delay(0.15);

		}
	}
	
	//sets specific color based on enum
	public static void setColor(Colors colors) {
		switch (colors) {
		case eRed:
			setColor(255, 0, 0);
			break;
		case eGreen:
			setColor(0, 255, 0);
			break;

		case eBlue:
			setColor(0, 0, 255);
			break;

		case ePink:
			setColor(255, 0, 255);
			break;

		case ePurple:
			setColor(255, 0, 127);
			break;

		case eOrange:
			setColor(255, 20, 0);
			break;

		case eWhite:
			setColor(255, 255, 255);
			break;

		case eTeal:
			setColor(0, 255, 255);
			break;
		}
	}

	//controls LED's manually based on a joystick R-axis,L-axis, and L-trigger
	//press A to log current color
	public static void manualControl(Joystick drivePad) {
		int red = (int) Math.abs(255 * drivePad.getRawAxis(1));
		int green = (int) Math.abs(255 * drivePad.getRawAxis(5));
		int blue = (int) Math.abs(255 * drivePad.getRawAxis(2));
		if (drivePad.getRawButton(1)) {
			int[] colorArray = new int[] { red, green, blue };
			ColorList.add(colorArray);
			valuesLogged = true;
		}
		setColor(red, green, blue);
	}
	//prints color logged in manualControl()
	//use after the while(isEnabled() && isOperatorControl()/isAutonomous()/isTest()) loop
	public static void logValues() {
		if (valuesLogged) {
			for (int x = 0; x < ColorList.size() - 1; x++) {
			}
		}
	}
}
