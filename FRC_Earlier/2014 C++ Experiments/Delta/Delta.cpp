#include "WPILib.h"
#include "Defines.h"
#include "Globals.h"
#include "Modules/MechanumDrive.h"
#include "Modules/Pneumatics.h"

#include "Modules/AfterADXL.h"

MechanumDrive *mechDriveTrain;
Pneumatics *piston;
Joystick *twistStick;

Joystick *driveStick;
AfterADXL *afterADXL;

class Delta : public SimpleRobot
{
public:
	Delta(void){
		GetWatchdog().SetExpiration(0.1);
		GetWatchdog().SetEnabled(false);
		
		mechDriveTrain = new MechanumDrive();
		//cannonPneumatics = new PneumaticCannons();
		
		piston = new Pneumatics();
		
		twistStick = new Joystick(JOYSTICK);
		
		driveStick = new Joystick(2);
		
		afterADXL = new AfterADXL();
		afterADXL->StartADXL();
		//accel = new ADXL345_I2C(1, ADXL345_I2C::kRange_2G);
	}

	void Autonomous(void)
	{
		GetWatchdog().SetEnabled(false);
		while(IsAutonomous()){	
			mechDriveTrain->AutonDrive();
		}
	}

	void OperatorControl(void)
	{
		GetWatchdog().SetEnabled(false);
		while (IsOperatorControl())
		{
			mechDriveTrain->Drive();
			piston->FirePiston();
			
			if(twistStick->GetRawButton(4)) {
				afterADXL->ResetDistance();
			}
			/*potValue = fabs((0.8 * (pot->GetAverageVoltage() / 5)) + .2);
			leftSol->Set(solVal);
			rightSol->Set(!solVal);
			printf("pot value:%f\n", potValue);
			if(solTime->HasPeriodPassed(potValue))
			{
				solVal = !solVal;
				solTime->Reset();
			}*/
		}
	}
};

START_ROBOT_CLASS(Delta);
