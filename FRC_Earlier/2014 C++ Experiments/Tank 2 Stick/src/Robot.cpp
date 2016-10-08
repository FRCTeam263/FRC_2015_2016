/*6 Wheel Drive Code.
 *
 * Developed by Team 263: Sachem Aftershock
 * Created by: Tejas Prasad
 */

#include "WPILib.h"
#include "6WheelDrive.h"
#include "NavXLib/IMU.h"

class Robot: public SampleRobot
{
	SixWD *drive;
	Joystick *drivePad;
	NetworkTable *table;
	IMU *imu;
	SerialPort *serial_port;
	bool first_iteration;

public:
	Robot()
	{
		drive = new SixWD();
		drivePad = new Joystick(0);

		if ( imu ) {
			LiveWindow::GetInstance()->AddSensor("IMU", "Gyro", imu);
		}
		first_iteration = true;
	}

	~Robot(){
		delete drive;
		delete drivePad;
	}

	void RobotInit() {

		table = NetworkTable::GetTable("datatable");
		serial_port = new SerialPort(57600,SerialPort::kMXP);
		uint8_t update_rate_hz = 50;
#if defined(ENABLE_AHRS)
		imu = new AHRS(serial_port,update_rate_hz);
#elif defined(ENABLE_IMU_ADVANCED)
		imu = new IMUAdvanced(serial_port,update_rate_hz);
#else // ENABLE_IMU
		imu = new IMU(serial_port,update_rate_hz);
#endif
		if ( imu ) {
			LiveWindow::GetInstance()->AddSensor("IMU", "Gyro", imu);
		}
		first_iteration = true;
	}

	void Autonomous()
	{
	}

	void OperatorControl()
	{
		while (IsOperatorControl() && IsEnabled())
		{
			drive->Drive(drivePad);
			if ( first_iteration ) {
				bool is_calibrating = imu->IsCalibrating();
				if ( !is_calibrating ) {
					Wait( 0.3 );
					imu->ZeroYaw();
					first_iteration = false;
				}
			}
			SmartDashboard::PutBoolean( "IMU_Connected", imu->IsConnected());
			SmartDashboard::PutNumber("IMU_Yaw", imu->GetYaw());
			SmartDashboard::PutNumber("IMU_Pitch", imu->GetPitch());
			SmartDashboard::PutNumber("IMU_Roll", imu->GetRoll());
			SmartDashboard::PutNumber("IMU_CompassHeading", imu->GetCompassHeading());
			SmartDashboard::PutNumber("IMU_Update_Count", imu->GetUpdateCount());
			SmartDashboard::PutNumber("IMU_Byte_Count", imu->GetByteCount());
		}
	}
};

START_ROBOT_CLASS(Robot);
