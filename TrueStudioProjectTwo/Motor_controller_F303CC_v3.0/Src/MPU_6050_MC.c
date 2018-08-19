/*
 * MPU_6050.c
 *
 *  Created on: 3 Jun 2018
 *      Author: Piotr Kozimor
 */

#include "MPU_6050_MC.h"

void MPU_6050_Init()
{
	drv_mpu6050_init(&m_handler, drv_mpu6050_device_0);
	drv_mpu6050_set_acc(&m_handler, &m_data_acc, drv_mpu6050_accelerometer_8g);
	drv_mpu6050_set_gyr(&m_handler, &m_data_gyr, drv_mpu6050_gyroscope_250s);
	drv_mpu6050_set_digital_lp_filter(&m_handler, drv_mpu6050_bandwidth_21Hz);
}

void MPU_6050_GetData()
{
	drv_mpu6050_read_acc(&m_handler,&m_data_acc);
	drv_mpu6050_read_gyr(&m_handler,&m_data_gyr);
}
