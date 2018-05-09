/*
 * ADC_MC.c
 *
 *  Created on: 6 May 2018
 *      Author: Piotr Kozimor
 */

#include "ADC_MC.h"

static struct ADC_MC_Data ADC_MC_Data_Instance;

void ADC1_MC_Init(void)
{
	if(HAL_ADC_Start_DMA(&hadc1,
						ADC_MC_Data_Instance.DataReceivedAPPS.forDMA,
						APPS_BuforLength)==HAL_OK)
		if(HAL_TIM_Base_Start(&htim6)==HAL_OK)
			SET_BIT(ADC_MC_Data_Instance.Status,ADC1_Tim6InitError);
		else
			SET_BIT(ADC_MC_Data_Instance.Status,ADC1_InitError);
	else
	{
		CLEAR_BIT(ADC_MC_Data_Instance.Status,ADC1_Tim6InitError);
		CLEAR_BIT(ADC_MC_Data_Instance.Status,ADC1_InitError);
	}
	//implement self calibration
};

void ADC2_MC_Init(void)
{
	if(HAL_ADC_Start_DMA(&hadc2,
						ADC_MC_Data_Instance.DataReceivedBSE.forDMA,
						BSE_HalfBuforLength*2)==HAL_OK)
		if(HAL_TIM_Base_Start(&htim7)==HAL_OK)
			SET_BIT(ADC_MC_Data_Instance.Status,ADC2_Tim7InitError);
		else
			SET_BIT(ADC_MC_Data_Instance.Status,ADC2_InitError);
	else
	{
		CLEAR_BIT(ADC_MC_Data_Instance.Status,ADC2_Tim7InitError);
		CLEAR_BIT(ADC_MC_Data_Instance.Status,ADC2_InitError);
	}
};

void ADC1_IRQ_Handler(void)
{
	arm_mean_q31(ADC_MC_Data_Instance.DataReceivedAPPS.forMean,
				APPS_BuforLength,
				&ADC_MC_Data_Instance.DataMeanedAPPS.toSend);
	ADC_MC_Data_Instance.DataToSend.APPS1=ADC_MC_Data_Instance.DataMeanedAPPS.fromMean[0];
	ADC_MC_Data_Instance.DataToSend.APPS2=ADC_MC_Data_Instance.DataMeanedAPPS.fromMean[1];
};

void ADC2_IRQ_Handler(void)
{
	arm_mean_q15(ADC_MC_Data_Instance.DataReceivedBSE.forMean,
				BSE_HalfBuforLength*2,
				&ADC_MC_Data_Instance.DataToSend.BSE);
};

void GetAPPS1_Data (uint16_t * DataPtr)
{
	*DataPtr=ADC_MC_Data_Instance.DataToSend.APPS1;
};
void GetAPPS2_Data (uint16_t * DataPtr)
{
	*DataPtr=ADC_MC_Data_Instance.DataToSend.APPS2;
};
void GetBSE_Data (uint16_t * DataPtr)
{
	*DataPtr=ADC_MC_Data_Instance.DataToSend.BSE;
};

uint16_t ADC_GetStatus(void)
{
	ADC_MC_Data_Instance.Status |= HAL_ADC_GetError(&hadc1)<<12;
	ADC_MC_Data_Instance.Status |= HAL_ADC_GetError(&hadc2)<<8;
	return ADC_MC_Data_Instance.Status;
};

