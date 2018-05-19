/*
 * GPIO_MC.c
 *
 *  Created on: 13 May 2018
 *      Author: Piotr
 */

#include "../Modules_inc/GPIO_MC.h"

void WritePrecharge(uint8_t Val)
{
	HAL_GPIO_WritePin(PreCharge_GPIO_Port,PreCharge_Pin,Val);
};

void WriteRDY(uint8_t Val)
{
	HAL_GPIO_WritePin(RDY_GPIO_Port,RDY_Pin,Val);
};
void WriteLED_Green(uint8_t Val)
{
	HAL_GPIO_WritePin(LED_G_GPIO_Port,LED_G_Pin,Val);
};
void WriteLED_Red(uint8_t Val)
{
	HAL_GPIO_WritePin(LED_R_GPIO_Port,LED_R_Pin,Val);
};
void WriteLED_Yellow(uint8_t Val)
{
	HAL_GPIO_WritePin(LED_Y_GPIO_Port,LED_Y_Pin,Val);
};
uint8_t GetStartButton(void)
{
	return HAL_GPIO_ReadPin(StartButton_GPIO_Port,StartButton_Pin);
}
uint8_t GetRFE(void)
{
	return HAL_GPIO_ReadPin(RFE_GPIO_Port,RFE_Pin);
}
