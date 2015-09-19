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

