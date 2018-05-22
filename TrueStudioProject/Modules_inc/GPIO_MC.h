/*
 * GPIO_MC.h
 *
 *  Created on: 13 May 2018
 *      Author: Piotr
 */

#ifndef GPIO_MC_H_
#define GPIO_MC_H_

#include "gpio.h"

void WritePrecharge(uint8_t Val);
void WriteRDY(uint8_t Val);
void WriteLED_Green(uint8_t Val);
void WriteLED_Red(uint8_t Val);
void WriteLED_Yellow(uint8_t Val);
uint8_t GetStartButton(void);
uint8_t GetRFE(void);



#endif /* GPIO_MC_H_ */
