/*
 * MPU_6050.h
 *
 *  Created on: 3 Jun 2018
 *      Author: Piotr Kozimor
 */

#ifndef MPU_6050_MC_H_
#define MPU_6050_MC_H_

#include "drv_mpu6050.h"
#include "drv_mpu6050_hal.h"
#include "drv_mpu6050_reg.h"

static drv_mpu6050_t      m_handler;
static drv_mpu6050_data_t m_data_acc;
static drv_mpu6050_data_t m_data_gyr;

void MPU_6050_Init();
void MPU_6050_GetData() __attribute__((section(".ccmram")));




#endif /* MPU_6050_MC_H_ */
