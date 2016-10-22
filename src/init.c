/**
 * File for initialization code.
 *
 * This file should contain the user initialize() function and any functions related to it.
 *
 * Copyright(c) 2011 - 2014, Purdue University ACM SIG BOTS.All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met :
 *
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and / or other materials provided with the distribution.
 * Neither the name of Purdue University ACM SIG BOTS nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS(http://www.freertos.org) whose source code may be obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"

int g_IntakeForkState;
Gyro mainGyro;
// Slew Rate Enabled?
_Bool LIFT_SLEW_CONTROL_ENABLED;
_Bool BASE_SLEW_CONTROL_ENABLED;

/**
 * Runs pre-initialization code.
 *
 * This function will be started in kernel mode one time while the VEX Cortex is starting up. As the scheduler is still paused, most API functions will fail.
 *
 * The purpose of this function is solely to set the default pin modes (pinMode()) and port states (digitalWrite()) of limit switches, push buttons, and solenoids. It can also safely configure a UART port (usartOpen()) but cannot set up an LCD (lcdInit()).
 */
void initializeIO() {

	pinMode(SOL_LEFT, OUTPUT);
	pinMode(SOL_RIGHT, OUTPUT);

	digitalWrite(SOL_LEFT, 0);
	digitalWrite(SOL_RIGHT, 0);

	g_IntakeForkState = 0;
}

/**
 * Runs user initialization code.
 *
 * This function will be started in its own task with the default priority and stack size once when the robot is starting up. It is possible that the VEXnet communication link may not be fully established at this time, so reading from the VEX Joystick may fail.
 *
 * This function should initialize most sensors (gyro, encoders, ultrasonics), LCDs, global variables, and IMEs.
 *
 * This function must exit relatively promptly, or the operatorControl() and autonomous() tasks will not start. An autonomous mode selection menu like the pre_auton() in other environments can be implemented in this task if desired.
 */

void initialize() {


//	addMotor(MOTOR_BASE_FRONT_LEFT, MOTOR_SLOW_SLEW_RATE);
//	addMotor(MOTOR_BASE_FRONT_RIGHT, MOTOR_SLOW_SLEW_RATE);
//	addMotor(MOTOR_BASE_BACK_LEFT, MOTOR_SLOW_SLEW_RATE);
//	addMotor(MOTOR_BASE_BACK_RIGHT, MOTOR_SLOW_SLEW_RATE);
//	addMotor(MOTOR_LIFT_LEFT_TOP, LIFT_SLOW_SLEW_RATE);
//	addMotor(MOTOR_LIFT_LEFT_BOT, LIFT_SLOW_SLEW_RATE);
//	addMotor(MOTOR_LFIT_RIGHT_TOP, LIFT_SLOW_SLEW_RATE);
//	addMotor(MOTOR_LIFT_RIGHT_TOP, LIFT_SLOW_SLEW_RATE);


	lcdInit(LCD_PORT);
	lcdClear(LCD_PORT);
	lcdSetBacklight(LCD_PORT, true);
	lcdPrint(LCD_PORT, 1, " ROBOT STARTING ");
	lcdPrint(LCD_PORT, 2, "  PLEASE WAIT   ");

	if (imeInitializeAll() != 4) {
		lcdClear(LCD_PORT);
		lcdPrint(LCD_PORT, 1, "Not all IME's Found");
		printf("Not all IMEs were found\r\n");
	}



	//mainGyro = gyroInit(GYRO_PORT, 0);

	//delay(600);

	return;
}
