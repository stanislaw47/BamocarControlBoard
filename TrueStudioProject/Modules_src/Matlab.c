/*
 * Matlab.c
 *
 *  Created on: 9 May 2018
 *      Author: Piotr
 */

#include "Matlab.h"

void Matlab_Init(void)
{
	motor_simple_initialize();
};

void Matlab_Step(void)
{
	GetAPPS2_Data(&rtU.pos);
	motor_simple_step();
	CAN_MC_TorqueCommand(rtY.CAN_command);
};
