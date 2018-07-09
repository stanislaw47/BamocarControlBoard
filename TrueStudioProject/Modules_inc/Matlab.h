/*
 * Matlab.h
 *
 *  Created on: 9 May 2018
 *      Author: Piotr
 */

#ifndef MATLAB_H_
#define MATLAB_H_

#include "motor_simple.h"
#include "ADC_MC.h"
#include "CAN_MC.h"
#include "GPIO_MC.h"

void Matlab_Init(void);
void Matlab_Step(void)  __attribute__((section(".ccmram")));

#endif /* MATLAB_H_ */
