/*
 * ADC_MC.c
 *
 *  Created on: 6 May 2018
 *      Author: Piotr Kozimor
 */

#include "ADC_MC.h"

static struct ADC_MC_Data ADC_MC_Data_Instance;

ADC_StatusTypeDef ADC_MC_Init(void)
{
	if(HAL_ADC_Start_DMA(&hadc1,ADC_MC_Data_Instance.DataReceivedAPPS.forDMA,APPS_BuforLength)==HAL_OK)
		if(HAL_TIM_Base_Start(&htim6)==HAL_OK)
			ADC_MC_Data_Instance.Status=ADC_OK;
		else
			ADC_MC_Data_Instance.Status=ADC_TIM_Err;
	else
		ADC_MC_Data_Instance.Status=ADC_Error;
	return ADC_MC_Data_Instance.Status;
};

void ADC_IRQ_Handler(void)
{

};
