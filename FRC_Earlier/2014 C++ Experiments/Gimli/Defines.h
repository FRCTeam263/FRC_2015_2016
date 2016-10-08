#ifndef DEFINES_H_
#define DEFINES_H_

#define POT_MIN 4
#define POT_MAX 500

//Joysticks
#define DRIVEPAD 1
#define GAMEPAD 2

//PWM
#define FRONT_LEFT_MOTOR 1
#define BACK_LEFT_MOTOR 2
#define FRONT_RIGHT_MOTOR 3
#define BACK_RIGHT_MOTOR 4
#define SHOOTER_MOTOR 5
#define SHOOTER_MOTOR_2 6

//Analog
#define GYRO 1
#define SHOOTER_POT 2
#define ULTRASONIC_SENSOR 4

//Relay
#define COMPRESSOR 1
#define PICKUP_MOTOR 2

//Solenoid
#define PICKUP_PISTON_1 3
#define PICKUP_PISTON_2 4

//Digital
#define PRESSURE_SWTICH 1
#define LIMIT_SWITCH 2
#define SHOOTER_ENCODER_A 3
#define SHOOTER_ENCODER_B 4

//Camera constants used for distance calculation
#define Y_IMAGE_RES 480		//X Image resolution in pixels, should be 120, 240 or 480
#define VIEW_ANGLE 49		//Axis M1013
//#define VIEW_ANGLE 41.7		//Axis 206 camera
//#define VIEW_ANGLE 37.4  //Axis M1011 camera
#define PI 3.141592653

//Score limits used for target identification
#define RECTANGULARITY_LIMIT 40
#define ASPECT_RATIO_LIMIT 55

//Score limits used for hot target determination
#define TAPE_WIDTH_LIMIT 50
#define VERTICAL_SCORE_LIMIT 50
#define LR_SCORE_LIMIT 50

//Minimum area of particles to be considered
#define AREA_MINIMUM 150

//Maximum number of particles to process
#define MAX_PARTICLES 8

#endif
