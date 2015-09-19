#include "WPILib.h"
#include "liftsystem.h"


#define Button_A_1 1
#define Button_B_2 2
#define Button_X_3 3
#define Button_Y_4 4
#define Button_LeftBumper 5
#define Button_RightBumper 6
#define Button_LeftTrigger 7
#define Button_RightTrigger 8
#define Button_Start 9
#define Button_Select 10
#define Button_L3 11
#define Button_R3 12

#define Axis_LeftStick_Horizontal 0
#define Axis_LeftStick_Vertical 1 // min StickForward = -1 , stick down = 1, rest = 0.023622
#define Axis_LeftTrigger 2 // Min Return Value = 0, Max return value = 1. Rest state is 0
#define Axis_RightTrigger 3 // Min Return Value = 0, Max return value = 1. Rest state is 0
#define Axis_RightStick_Horizontal 4
#define Axis_RightStick_Vertical 5


#define Idle -1
#define North 0
#define NorthEast 45
#define East 90
#define SouthEast 135
#define South 180
#define SouthWest 225
#define West 270
#define NorthWest 315

class Robot: public SampleRobot {
private:
	liftmotor *lifter;
	Joystick *GameController;

public:
	Robot() {
		lifter = new liftmotor;
		GameController = new Joystick(0);
	}

	void Autonomous() {

	}
	void OperatorControl() {
		float LeftStickHorizDir = 0;
		float LeftStickVertDir = 0;
		float RightStickHorizDir = 0;
		float RightStickVertDir = 0;
		float LeftTriggerDir = 0;
		float RightTriggerDir = 0;
		int but1 = 0;
		int but2 = 0;
		int but3 = 0;
		int but4 = 0;
		int but5 = 0;
		int but6 = 0;
		int but7 = 0;
		int but8 = 0;
		int pov = 0;

		while (IsOperatorControl() && IsEnabled()) {
			lifter->LiftTote(GameController);

			LeftStickHorizDir = GameController->GetRawAxis(Axis_LeftStick_Vertical);
			printf("Axis(%d) = %f\n", Axis_LeftStick_Vertical ,LeftStickHorizDir);
			LeftStickHorizDir = GameController->GetRawAxis(Axis_LeftTrigger);
			printf("Axis(%d) = %f\n", Axis_LeftTrigger ,LeftStickHorizDir);
			LeftStickHorizDir = GameController->GetRawAxis(Axis_RightTrigger);
			printf("Axis(%d) = %f\n", Axis_RightTrigger ,LeftStickHorizDir);
			LeftStickHorizDir = GameController->GetRawAxis(Axis_RightStick_Horizontal);
			printf("Axis(%d) = %f\n", Axis_RightStick_Horizontal ,LeftStickHorizDir);
			LeftStickHorizDir = GameController->GetRawAxis(Axis_RightStick_Vertical);
			printf("Axis(%d) = %f\n", Axis_RightStick_Vertical ,LeftStickHorizDir);
			LeftStickHorizDir = GameController->GetRawAxis(Axis_LeftStick_Horizontal);
			printf("Axis(%d) = %f\n", Axis_LeftStick_Horizontal ,LeftStickHorizDir);

			but1 = GameController->GetRawButton(Button_A_1);
			printf("Button(%d) = %d\n",Button_A_1, but1);
			but2 = GameController->GetRawButton(Button_B_2);
			printf("Button(%d) = %d\n",Button_B_2, but2);
			but3 = GameController->GetRawButton(Button_X_3);
			printf("Button(%d) = %d\n",Button_X_3, but3);
			but4 = GameController->GetRawButton(Button_Y_4);
			printf("Button(%d) = %d\n", Button_Y_4,but4);
			but5 = GameController->GetRawButton(Button_LeftBumper);
			printf("Button(%d) = %d\n", Button_LeftBumper,but5);
			but6 = GameController->GetRawButton(Button_RightBumper);
			printf("Button(%d) = %d\n", Button_RightBumper,but6);
			but7 = GameController->GetRawButton(Button_LeftTrigger);
			printf("Button(%d) = %d\n", Button_LeftTrigger,but7);
			but8 = GameController->GetRawButton(Button_RightTrigger);
			printf("Button(%d) = %d\n", Button_RightTrigger,but8);

			pov = GameController->GetPOV();
			printf("POV %d\n",pov);
			Wait(1);
		}
	}

};

START_ROBOT_CLASS(Robot);
