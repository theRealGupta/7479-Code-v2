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
_Bool LIFT_SLEW_CONTROL_ENABLED, BASE_SLEW_CONTROL_ENABLED;

Encoder enc_baseLeft, enc_baseRight, enc_liftLeft, enc_liftRight;

OdometricLocalizer mainOdo;

/**
 * Runs pre-initialization code.
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
 */
void initialize() {
    addMotor(MOTOR_BASE_FRONT_LEFT, MOTOR_SLOW_SLEW_RATE);
    addMotor(MOTOR_BASE_FRONT_RIGHT, MOTOR_SLOW_SLEW_RATE);
    addMotor(MOTOR_BASE_BACK_LEFT, MOTOR_SLOW_SLEW_RATE);
    addMotor(MOTOR_BASE_BACK_RIGHT, MOTOR_SLOW_SLEW_RATE);
    addMotor(MOTOR_LIFT_LEFT_TOP, LIFT_SLOW_SLEW_RATE);
    addMotor(MOTOR_LIFT_LEFT_BOT, LIFT_SLOW_SLEW_RATE);
    addMotor(MOTOR_LFIT_RIGHT_TOP, LIFT_SLOW_SLEW_RATE);
    addMotor(MOTOR_LIFT_RIGHT_TOP, LIFT_SLOW_SLEW_RATE);

// TODO: Add values
    init_OdometricLocalizer(&mainOdo, Optical, NULL, NULL, 360.0);

    lcdInit(LCD_PORT);
    lcdClear(LCD_PORT);
    lcdSetBacklight(LCD_PORT, true);

    lcdPrint(LCD_PORT, 1, " ROBOT STARTING ");
    lcdPrint(LCD_PORT, 2, "  PLEASE WAIT   ");

    enc_baseLeft = encoderInit(QUAD_BASE_LEFT, QUAD_BASE_LEFT_2, true);
    enc_baseRight = encoderInit(QUAD_BASE_RIGHT, QUAD_BASE_RIGHT_2, false);
    enc_liftLeft = encoderInit(QUAD_LIFT_LEFT, QUAD_LIFT_LEFT_2, true);
    enc_liftRight = encoderInit(QUAD_LIFT_RIGHT, QUAD_LIFT_RIGHT_2, false);

    //mainGyro = gyroInit(GYRO_PORT, 0);

    return;
}
