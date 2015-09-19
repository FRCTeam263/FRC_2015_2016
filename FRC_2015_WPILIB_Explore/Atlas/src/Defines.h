#ifndef SRC_SYSTEMS_DEFINES_H_
#define SRC_SYSTEMS_DEFINES_H_

//CAN Motors
#define FRONT_LEFT_MOTOR 1
#define FRONT_RIGHT_MOTOR 0
#define BACK_LEFT_MOTOR 2
#define BACK_RIGHT_MOTOR 5

#define CAN_LIFT_MOTOR 8
#define SHORT_LIFT_MOTOR_1 3
#define SHORT_LIFT_MOTOR_2 6

//DIO
#define SHORT_BOTTOM_LS 4
#define SHORT_TOP_LS 3
#define CAN_BOTTOM_LS 1
#define CAN_TOP_LS 0
#define LONG_TOTE_SENSOR 6
#define SHORT_TOTE_SENSOR 8

//Analog Input
#define GYRO 0


//Pnuematic Control Module (PCM)
#define PIVOT_PISTON_FORWARD_CHANNEL 0
#define PIVOT_PISTON_REVERSE_CHANNEL 1


//Const
const int elevatorShortLevels[6] = {0, 856, 1560, 2700, 4400, 1660};
const int elevatorCanLevels[6] = {0, 1000, 1973, 3500, 1950, 2400};
const int autonDrive1[8] = {0, 480, 4300, 6340, 6470, 8300, 7640, 9000};
const int autonDrive2[5] = {0, 450, 200, 300, 400};

#endif /* SRC_SYSTEMS_DEFINES_H_ */
