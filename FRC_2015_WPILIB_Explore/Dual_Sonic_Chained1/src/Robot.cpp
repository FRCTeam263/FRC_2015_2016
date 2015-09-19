// Dual_Sonic
// Used to test the Dual Sonic sensor wired configuration of
// cascaded sensors.

#include "WPILib.h"



class Robot: public SampleRobot {

	DigitalOutput *exampleDigital;
	AnalogInput *exampleInput1;
	AnalogInput *exampleInput2;

public:

	Robot() {
		exampleDigital = new DigitalOutput(5);
		exampleInput1 = new AnalogInput(2);
		exampleInput2 = new AnalogInput(3);

		// Pulse the trigger to kick off continuous mode of sonic sensors cascaded.
		exampleDigital->Set(0);
		Wait(0.010); // milliseconds
		exampleDigital->Set(1);
		Wait(0.010); // milliseconds
		exampleDigital->Set(0);
		Wait(0.010); // milliseconds

	}

	~Robot() {
		delete exampleDigital;
		delete exampleInput1;
		delete exampleInput2;
	}

	void Autonomous() {

	}

	void OperatorControl() {
		float Sonic1Inches = 0.0;
		float Sonic2Inches = 0.0;
		bool ToteAligned = false;
		const float minxRangeClearanceRequiredInInches = 24;

		// code for float Sonic1Inches = 0.0.
		while (IsEnabled() && IsOperatorControl()) {

			Sonic1Inches = exampleInput1->GetVoltage();
			float Sonic1InchesInInches = Sonic1Inches * (512 / 5);
			printf("sonicReturn = %f,	inches = %f feet=%f	\n", Sonic1Inches,
					Sonic1InchesInInches, Sonic1InchesInInches / 12);

			Sonic1Inches = exampleInput2->GetVoltage();
			float Sonic2InchesInInches = Sonic2Inches * (512 / 5);
			printf("sonicReturn = %f,	inches = %f feet=%f	\n", Sonic2Inches,
					Sonic2InchesInInches, Sonic2InchesInInches / 12);

			ToteAligned = (Sonic1Inches > minxRangeClearanceRequiredInInches)
					&& (Sonic2Inches > minxRangeClearanceRequiredInInches);
			printf("Tote Aligned: %d\n\n", ToteAligned);
		}

	}

	void Test() {

	}
};

START_ROBOT_CLASS(Robot);
