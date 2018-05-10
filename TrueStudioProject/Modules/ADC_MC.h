/*
 * ADC_MC.h
 *
 *  Created on: 6 May 2018
 *      Author: Piotr Kozimor
 */

#ifndef MODULES_ADC_MC_H_
#define MODULES_ADC_MC_H_

//Cortex M4 family
#define ARM_MATH_CM4

//Prevents warnings (inproper including order), defined also in stmf303xc.h file
#define __FPU_PRESENT             1U       /*!< STM32F303xC devices provide an FPU */
#include "arm_math.h"

#include "adc.h"
#include "tim.h"

#define ADC1_InitError 		0x01
#define ADC1_Tim6InitError	0x02
#define ADC2_InitError 		0x04
#define ADC2_Tim7InitError	0x08

//DMA interrupt will occur after following number of ADC scans (for APPS)
#define APPS_BuforLength 50

//DMA interrupt will occur after following number of ADC scans (for BSE)
#define BSE_HalfBuforLength 25

struct ADC_MC_Data
{
	union DataReceivedAPPS
	{
		uint32_t forDMA[APPS_BuforLength];
		uint16_t forMean[APPS_BuforLength][2];
		uint16_t forTests[APPS_BuforLength*2];
	} DataReceivedAPPS;
	uint16_t APPS_MeanBufor[APPS_BuforLength];
	union DataReceivedBSE
	{
		uint32_t forDMA[BSE_HalfBuforLength];
		uint16_t forMean[BSE_HalfBuforLength*2];
	} DataReceivedBSE;
	struct DataToSend
	{
		uint16_t BSE;
		uint16_t APPS1;
		uint16_t APPS2;
	} DataToSend;
	uint16_t Status;
};


void ADC1_MC_Init(void);
void ADC2_MC_Init(void);
void GetAPPS1_Data (uint16_t * DataPtr);
void GetAPPS2_Data (uint16_t * DataPtr);
void GetBSE_Data (uint16_t * DataPtr);
void ADC1_IRQ_Handler(void);
void ADC2_IRQ_Handler(void);
uint16_t ADC_GetStatus(void);

#endif /* MODULES_ADC_MC_H_ */
