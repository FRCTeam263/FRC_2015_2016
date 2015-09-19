#include <string>
#include "WPILib.h"

class Robot: public SampleRobot {

public:
	Robot() {

	}
	~Robot() {

	}

	void Autonomous() {

	}

	void OperatorControl() {
		int a[5] = { 16, 4, 3, 12, 7 };
		printf("The Initial Array Contains: \n");
		for(int x = 0; x < 5; x++)
		{
			printf("%d ",a[x]);
		}
		printf("\nThe Sorted Array Is: \n");
		int b = 1;
		for(int i = 0; i < 5-1;i++)
		{
			for(int j = i+1; j < 5; j++)
			{
				if(a[j]<a[i])
				{
					// Swap Elements
					 //b = *(a+j);
					  b = a[i];
					 a[i] = a[j];
					 a[j] = b;
				}
			}
		}
		for(int x = 0; x < 5; x++)
		{
			printf("%d ",a[x]);
		}
		printf("\nGoodbye \n");
	}



	void Test() {
	}
};

START_ROBOT_CLASS(Robot);
