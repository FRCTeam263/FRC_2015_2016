#include "Utilities.h"

Utilities::Utilities(void){

}

Utilities::~Utilities(void){

}

float Utilities::DeadBand(float input, float deadband){

	if(fabs(input) <= deadband){
		return 0.0f;
	}

	return input;
}

float Utilities::MaxValue(float input, float min, float max){

	if(input > max){
		input = max;
	}
	else if(input < min){
		input = min;
	}
	return input;
}

bool Utilities::GetJoystickButton(int RawButton, Joystick *HID){
	const int maxButtons = 25;
	static int lastButtonValue[maxButtons];
	int currentButtonValue = 0;
	bool currentPressedState = false;

	static bool firstTimeCalled = true;
	if(firstTimeCalled){
		for(int i = 0; i < maxButtons; i++){
			lastButtonValue[i] = 0;
		}
		firstTimeCalled = false;
	}

	currentButtonValue = HID->GetRawButton(RawButton);

	//printf("Current %d\t Last: %d\n", currentButtonValue, lastButtonValue[RawButton]);

	if ((lastButtonValue[RawButton] == 0) && (currentButtonValue == 1)) {
		currentPressedState = true;

	}
	else{
		currentPressedState = false;
	}
	lastButtonValue[RawButton] = currentButtonValue;

	return currentPressedState;
}

void Utilities::LimitSwitchRumble(Joystick *HID, DigitalInput *LS, float RumbleLength, bool HardRumble){
	const float rumbleTimeOut = RumbleLength;
	static int lastLSValue = 0;
	int currentLSValue = 0;
	static Timer rumbleTimer;
	rumbleTimer.Start();

	currentLSValue = LS->Get();
	if(lastLSValue == 0 && currentLSValue == 1){
		rumbleTimer.Reset();
		rumbleTimer.Start();

		if(HardRumble == true){
			HID->SetRumble(Joystick::kLeftRumble, 0.3);
		}
		else if(HardRumble == false){
			HID->SetRumble(Joystick::kRightRumble, 0.3);
		}
	}
	else if(lastLSValue == 1 && currentLSValue == 0){
		if(HardRumble == true){
			HID->SetRumble(Joystick::kLeftRumble, 0);
		}
		else if(HardRumble == false){
			HID->SetRumble(Joystick::kRightRumble, 0);
		}
	}
	else if(rumbleTimer.HasPeriodPassed(rumbleTimeOut)){
		if(HardRumble == true){
			HID->SetRumble(Joystick::kLeftRumble, 0);
		}
		else if(HardRumble == false){
			HID->SetRumble(Joystick::kRightRumble, 0);
		}
	}

	lastLSValue = currentLSValue;
}
