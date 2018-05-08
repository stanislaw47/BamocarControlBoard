/*
 * ADC_MC.h
 *
 *  Created on: 6 May 2018
 *      Author: Piotr Kozimor
 */

#ifndef MODULES_ADC_MC_H_
#define MODULES_ADC_MC_H_

#include "adc.h"
#include "tim.h"

//DMA interrupt will occur after following numer of ADC scans (for APPS)
#define APPS_BuforLength 50

//DMA interrupt will occur after following numer of ADC scans (for BSE)
#define BSE_BuforLength 50

struct ADC_MC_Data
{
	union DataReceivedAPPS
	{
		uint16_t forDMA[APPS_BuforLength*2];
		uint16_t forMean[APPS_BuforLength][2];
	} DataReceivedAPPS;
	union DataReceivedBSE
	{
		uint16_t forDMA[BSE_BuforLength];
		uint16_t forMean[BSE_BuforLength];
	} DataReceivedBSE;
	struct DataToSend
	{
		uint16_t BSE;
		uint16_t APPS1;
		uint16_t APPS2;
	} DataToSend;
	uint8_t Status;
};

typedef enum ADC_StatusTypeDef
{
	ADC_OK		=0,
	ADC_RxBusy	=1,
	ADC_TxBusy	=2,
	ADC_Error	=3,
	ADC_TIM_Err	=4
} ADC_StatusTypeDef;

ADC_StatusTypeDef ADC_MC_Init(void);
void GetAPPS1_Data (uint16_t * DataPtr);
void GetAPPS2_Data (uint16_t * DataPtr);
void GetBSE_Data (uint16_t * DataPtr);
ADC_StatusTypeDef ADC_Lock(void);
void ADC_Unlock(void);
void ADC_IRQ_Handler(void);


#endif /* MODULES_ADC_MC_H_ */
