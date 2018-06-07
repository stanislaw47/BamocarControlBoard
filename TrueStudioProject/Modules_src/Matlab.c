/*
 * Matlab.c
 *
 *  Created on: 9 May 2018
 *      Author: Piotr
 */

#include "Matlab.h"

void Matlab_Init(void)
{
	Motor_initialize();
};

void Matlab_Step(void)
{
	//GetAPPS1_Data(&rtU.APPS1);
	//GetAPPS2_Data(&rtU.APPS2);
	//GetBSE_Data(&rtU.BrakeEncoder);
	//rtU.RFE=GetRFE();
	//rtU.START=GetStartButton();

	Motor_step();

	//CAN_MC_TorqueCommand(rtY.BamocarTorqueLimit);
	//CAN_MC_CurrentLimitCommand(rtY.BamocarTorqueOut_CAN);
	//WritePrecharge(rtY.PRECH);
	//WriteRDY(rtY.RDY);
};
