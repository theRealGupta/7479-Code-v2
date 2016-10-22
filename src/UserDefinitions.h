/*
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       * UserDefinitions.h
 *
 *  Created on: Oct 4, 2016
 *      Author: natty
 */

#ifndef SRC_USERDEFINITIONS_H_
#define SRC_USERDEFINITIONS_H_

// Math

// Fast non-branching sign function
#define sign(x) (x > 0) - (x < 0)

#define PI M_PI

#define half(v) ((v) / 2.0)
#define square(v) ((v) * (v))
#define cube(v) ((v) * (v) * (v))
#define cubeRoot(v) ( pow(v, (1/3))  )
#define inchesToTicks(i, d) ( ((i) / (PI * (d))) * 360 )
#define ticksToInches(t, d) ( ((d) * PI) * ((t) / 360) )
#define inchToCm(i) ( i * 2.54 )
#define cmToInch(i) ( i / 2.54 )

#define radToDeg(i) (i * (180 / PI))
#define degToRad(i) (i * (PI / 180))

#define mapCubic(i) ((2*cube(i))/48387) + (i/3)

#define DRIVE_ENABLED true
#define LIFT_ENABLED true
#define LOCALIZER_ENABLED false

#define LOW_TICKS_PER_REV 627.2
#define HIGH_TICKS_PER_REV 392
#define TURBO_TICKS_PER_REV 216.333

// FIXME: Recalculate Lift sensor limits
#define LIFT_UPPER_LIMIT 1250
#define LIFT_HALF_LIMIT 500
#define LIFT_LOWER_LIMIT -25

// Number of sensor counts per single revolution
#define BASE_IME_COUNTS_PER_REV 392.0
// Diameter of wheels
#define BASE_WHEEL_DIAMETER 4.0
// Track width measured between centers of wheels
#define BASE_TRACK_WIDTH 15.0

// FIXME: Update wheel diam. and track width with actual values for idler wheels
// Number of sensor counts per single revolution of Idle wheels
#define IDLE_COUNTS_PER_REVOLUTION 360.0
// Diameter of Idler wheels
#define IDLE_WHEEL_DIAMETER 1234
// Track width of Idler wheels
#define IDLE_TRACK_WIDTH 1234

// Method of driving using the joysticks
// true = TANK DRIVE
// false = ARCADE DRIVE
#define DRIVE_TYPE true

#define JOYSTICK_THRESHOLD 10

// Motor Defines
#define MOTOR_BASE_FRONT_LEFT 2
#define MOTOR_BASE_FRONT_RIGHT 3  // Reversed
#define MOTOR_LIFT_LEFT_TOP 4
#define MOTOR_LIFT_LEFT_BOT 5
#define MOTOR_LIFT_RIGHT_TOP 6    // Reversed
#define MOTOR_LFIT_RIGHT_TOP 7    // Reversed
#define MOTOR_BASE_BACK_RIGHT 8   // Reversed
#define MOTOR_BASE_BACK_LEFT 9

// IME Defines
#define IME_BASE_LEFT 0
#define IME_BASE_RIGHT 1
#define IME_LIFT_RIGHT 2
#define IME_LIFT_LEFT 3

// Joystick Defines
#define JOY_JOY_LV 3
#define JOY_JOY_LH 4
#define JOY_JOY_RV 2
#define JOY_JOY_RH 1
#define JOY_BTN_LEFT 7
#define JOY_BTN_RIGHT 8
#define JOY_TRIG_LEFT 5
#define JOY_TRIG_RIGHT 6

// Solenoid Ports (Digital)
#define SOL_LEFT  1
#define SOL_RIGHT 2

//LCD Port
#define LCD_PORT uart1

// Gyro Port (Analog)
#define GYRO_PORT 1

typedef enum t_Direction {
	LEFT, RIGHT
} Direction;

#endif /* SRC_USERDEFINITIONS_H_ */
