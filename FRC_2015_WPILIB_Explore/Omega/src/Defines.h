#ifndef SRC_SYSTEMS_DEFINES_H_
#define SRC_SYSTEMS_DEFINES_H_

//CAN Motors
#define FRONT_LEFT_MOTOR 1
#define FRONT_RIGHT_MOTOR 0
#define BACK_LEFT_MOTOR 2
#define BACK_RIGHT_MOTOR 5

#define CAN_LIFT_MOTOR 4
#define SHORT_LIFT_MOTOR_1 7
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

//Const
const int elevatorShortLevels[5] = {0, 700, 1460, 2700, 3700};
const int elevatorCanLevels[5] = {0, 500, 1000, 3750, 2050};
const int autonDrive1[5] = {0, 280, 4470, 6000, 6470};
const int autonDrive2[5] = {0, 180, 200, 300, 400};

#endif /* SRC_SYSTEMS_DEFINES_H_ */
