/*
 * motorControlFunctions.c
 *
 *  Created on: Sep 28, 2016
 *      Author: user
 */

#include "main.h"
#include "motorControlFunctions.h"

_Bool LIFT_SLEW_CONTROL_ENABLED, BASE_SLEW_CONTROL_ENABLED;

int g_LiftLeftEncoder, g_LiftRightEncoder, g_BaseLeftEncoder,
		g_BaseRightEncoder, g_IntakeForkState;

/*
 * Set intake forks to specific state
 * INT-32 Values 1 = UP, 0 = DOWN
 */
int setIntakeForks(const int dir) {

	digitalWrite(SOL_LEFT, dir);
	digitalWrite(SOL_RIGHT, dir);
	g_IntakeForkState = dir;

	return 0;
}

/*
 * Toggles the intake state
 */
int toggleIntakeForks() {

	digitalWrite(SOL_LEFT, digitalRead(SOL_LEFT) == 1 ? 0 : 1);
	digitalWrite(SOL_RIGHT, digitalRead(SOL_RIGHT) == 1 ? 0 : 1);
	g_IntakeForkState = (digitalRead(SOL_RIGHT) == 1 ? 0 : 1);

	return 0;
}

/*
 * Sets power to left side of lift
 */
int setLiftLeft(const int power) {
//  if (!LIFT_ENABLED) return 1;
	switch (LIFT_SLEW_CONTROL_ENABLED) {

	case true:
		setMotorSpeed(MOTOR_LIFT_LEFT_TOP, (-1 * power));
		setMotorSpeed(MOTOR_LIFT_LEFT_BOT, (-1 * power));
		break;

	case false:
		motorSet(MOTOR_LIFT_LEFT_TOP, (-1 * power));
		motorSet(MOTOR_LIFT_LEFT_BOT, (-1 * power));
		break;

	}

	return 0;
}

/*
 * Sets power to right side of lift
 */
int setLiftRight(const int power) {

	switch (LIFT_SLEW_CONTROL_ENABLED) {

	case true:
		setMotorSpeed(MOTOR_LFIT_RIGHT_TOP, power);
		setMotorSpeed(MOTOR_LIFT_RIGHT_TOP, power);
		break;

	case false:
		motorSet(MOTOR_LFIT_RIGHT_TOP, power);
		motorSet(MOTOR_LIFT_RIGHT_TOP, power);
		break;
	}

	return 0;
}

/*
 * Sets power to left side of drivetrain
 */
int setDriveLeft(const int power) {

	switch (BASE_SLEW_CONTROL_ENABLED) {
	case true:
		setMotorSpeed(MOTOR_BASE_FRONT_LEFT, power);
		setMotorSpeed(MOTOR_BASE_BACK_LEFT, power);

		break;

	case false:
		motorSet(MOTOR_BASE_FRONT_LEFT, power);
		motorSet(MOTOR_BASE_BACK_LEFT, power);

		break;
	}
	return 0;
}

/*
 * Sets  power to right side of drivetrain
 */
int setDriveRight(const int power) {

	switch (BASE_SLEW_CONTROL_ENABLED) {

	case true:
		setMotorSpeed(MOTOR_BASE_FRONT_RIGHT, -1 * power);
		setMotorSpeed(MOTOR_BASE_BACK_RIGHT, -1 * power);
		break;

	case false:
		motorSet(MOTOR_BASE_FRONT_RIGHT, -1 * power);
		motorSet(MOTOR_BASE_BACK_RIGHT, -1 * power);
		break;

	}

	return 0;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Operates the lift                                          */
/*                                                                         */
/***************************************************************************/
int setLift(const int power) {
	int pMod = sign(abs(g_LiftLeftEncoder) - abs(g_LiftRightEncoder)) * power
			* 0.1;

	setLiftLeft(-1 * power);
	setLiftRight(-1 * (power + pMod));

	return 0;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Drives for time in milliseconds                            */
/*                                                                         */
/***************************************************************************/
int driveTime(const int l_power, const int r_power, const int timeMs) {
	int startingTime = millis();

	while (startingTime + timeMs > millis()) {
		setDriveLeft(l_power);
		setDriveRight(r_power);
	}

	setDriveLeft(0);
	setDriveRight(0);

	return 0;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Turns for time in milliseconds - Default: Turn Left        */
/*                                                                         */
/***************************************************************************/

int turnTime(const int power, const int timeMs) {
	int startingTime = millis();

	while (startingTime + timeMs > millis()) {
		setDriveLeft(-1 * power);
		setDriveRight(power);
	}

	setDriveLeft(0.5 * power);
	setDriveRight(-0.5 * power);
	delay(75);
	setDriveRight(0);
	setDriveLeft(0);

	return 0;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Turns for a distance in ticks Default: Turns Left          */
/*                                                                         */
/***************************************************************************/
int turnIME(const int power, const int ticks) {

	int dSide, pMod, initialLeft, initialRight, tempLeft, tempRight;

	initialLeft = g_BaseLeftEncoder;
	initialRight = g_BaseRightEncoder;

	tempLeft = g_BaseLeftEncoder;
	tempRight = g_BaseRightEncoder;
	while (g_BaseLeftEncoder < initialLeft + (ticks * 0.6)) {
		tempLeft = g_BaseLeftEncoder;
		tempRight = g_BaseRightEncoder;
		dSide = (tempLeft - initialLeft) - (tempRight - initialRight);
		pMod = sign(dSide) * power * 0.1;

		setDriveLeft(-1 * power);
		setDriveRight(power - pMod);

		delay(20);
	}

	while (g_BaseLeftEncoder < initialLeft + (ticks * 0.4)) {
		tempLeft = g_BaseLeftEncoder;
		tempRight = g_BaseRightEncoder;
		dSide = (tempLeft - initialLeft) - (tempRight - initialRight);
		pMod = sign(dSide) * power * 0.1;

		setDriveLeft((-1 * power / 3));
		setDriveRight((power - pMod) / 3);

		delay(20);
	}

	turnTime(-1 * (power / 2), 100);
	setDriveLeft(0);
	setDriveRight(0);

	return 0;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Turns for a specified angle at a given power               */
/*                                                                         */
/***************************************************************************/
int turnGyro(const int power, const int deg) {

	return 0;
}

/***************************************************************************/
/*                                                                         */
/* Subroutine - Drives for distance in ticks - Default: Forwards		   */
/*     TODO check pMod operand                                             */
/***************************************************************************/
int driveIME(const int power, const int ticks) {

	int dSide, pMod, initialLeft, initialRight, tempLeft, tempRight;

	initialLeft = g_BaseLeftEncoder;
	initialRight = g_BaseRightEncoder;

	tempLeft = g_BaseLeftEncoder;
	tempRight = g_BaseLeftEncoder;
	// Drive at full power for 80% of ticks
	while (tempLeft < initialLeft + (ticks * 0.8)) {
		tempLeft = g_BaseLeftEncoder;
		tempRight = g_BaseLeftEncoder;
		dSide = (tempLeft - initialLeft) - (tempRight - initialRight);
		pMod = sign(dSide) * power * 0.1;

		setDriveLeft(power);
		setDriveRight(power + pMod);

		delay(20);
	}

	// Drive at 1/3 Power for remaining 20% of ticks
	while (tempLeft < initialLeft + (ticks * 0.2)) {
		tempLeft = g_BaseLeftEncoder;
		tempRight = g_BaseLeftEncoder;
		dSide = (tempLeft - initialLeft) - (tempRight - initialRight);
		pMod = sign(dSide) * power * 0.1;

		setDriveLeft((power / 3));
		setDriveRight((power + pMod) / 3);

		delay(20);
	}

	// Stop
	driveTime(-0.5 * power, -0.5 * power, 100);
	setDriveLeft(0);
	setDriveRight(0);
	return 0;
}
/*
 * Calculates Joystick Dead-Zoning and returns value mapped to a cubic function
 */
int cJoyThreshold(int i) {
	if (abs(i) > JOYSTICK_THRESHOLD) {
		return mapCubic(i) * 0.8;
	} else {
		return 0.0;
	}
}

void joystickControlTask(void *ignore) {
	while (true) {
		imeGet(IME_LIFT_LEFT, &g_LiftLeftEncoder);
		imeGet(IME_LIFT_RIGHT, &g_LiftRightEncoder);
		imeGet(IME_BASE_LEFT, &g_BaseLeftEncoder);
		imeGet(IME_BASE_RIGHT, &g_BaseRightEncoder);

		g_LiftRightEncoder *= -1;
		g_BaseRightEncoder *= -1;
		switch (DRIVE_TYPE) {

		case false:
			setDriveLeft(
					cJoyThreshold(
							joystickGetAnalog(1, JOY_JOY_LV)
									+ joystickGetAnalog(1, JOY_JOY_LH)));
			setDriveRight(
					cJoyThreshold(
							joystickGetAnalog(1, JOY_JOY_LV)
									- joystickGetAnalog(1, JOY_JOY_LH)));
			break;

		case true:
			setDriveLeft(cJoyThreshold(joystickGetAnalog(1, JOY_JOY_LV)));
			setDriveRight(cJoyThreshold(joystickGetAnalog(1, JOY_JOY_RV)));
			break;

		}

		// Lift going up
		if (joystickGetDigital(1, 5, JOY_UP) == 1
				&& joystickGetDigital(1, 5, JOY_DOWN) != 1
				&& joystickGetDigital(1, 6, JOY_UP) != 1) {
			if (g_LiftLeftEncoder < LIFT_UPPER_LIMIT) {
				setLift(127);
			} else {
				setLift(0);
			}
		}

		// Lift going down
		if (joystickGetDigital(1, 5, JOY_UP) != 1
				&& joystickGetDigital(1, 5, JOY_DOWN) == 1
				&& joystickGetDigital(1, 6, JOY_UP) != 1) {
			if (g_LiftRightEncoder > LIFT_LOWER_LIMIT) {
				setLift(-127);
			} else {
				setLift(0);
			}
		}

		// Lift up and hold
		if (joystickGetDigital(1, 5, JOY_UP) != 1
				&& joystickGetDigital(1, 5, JOY_DOWN) != 1
				&& joystickGetDigital(1, 6, JOY_UP) == 1) {
			if (g_LiftRightEncoder < LIFT_HALF_LIMIT) {
				setLift(127);
			} else {
				setLift(0);
			}
		}

		// Lift doing nothing
		if (joystickGetDigital(1, 5, JOY_UP) != 1
				&& joystickGetDigital(1, 5, JOY_DOWN) != 1
				&& joystickGetDigital(1, 6, JOY_UP) != 1) {
			setLift(0);
		}

		delay(20);
	}
}

void imeUpdateTask(void *ignore) {
	while (true) {

		//lcdPrint(LCD_PORT, 1, "Stuff");
		delay(10);
	}
}
