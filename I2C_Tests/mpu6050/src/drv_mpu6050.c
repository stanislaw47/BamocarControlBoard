
/* LICENSE */

#include "app_config.h"
#include "drv_mpu6050.h"
#include "drv_mpu6050_reg.h"
#include "drv_mpu6050_hal.h"
#include <stdbool.h>

#define I2C_TIMEOUT_MS  	5

static uint8_t s_initialied_dev_mask = 0x00;

drv_mpu6050_result_t drv_mpu6050_init(drv_mpu6050_t* handler, drv_mpu6050_device_t dev_number)
{
	uint8_t id_value;
	uint8_t config_data[2];

	handler->drv_instance = drv_hal_i2c_init();

	if (!(s_initialied_dev_mask && (1<<dev_number)))
	{
		/* Format I2C address */
		handler->address = DRV_MPU6050_I2C_ADDR | (uint8_t)dev_number;

		/* Check if device is connected */
		if (drv_hal_i2c_is_dev_ready(handler->drv_instance, handler->address, I2C_TIMEOUT_MS) != DRV_HAL_OK)
		{
			return drv_mpu6050_device_not_connected;
		}

		/* Check who am I */
		if (drv_hal_i2c_mem_read(handler->drv_instance, handler->address, DRV_MPU6050_WHO_AM_I, 1, &id_value, 1, I2C_TIMEOUT_MS) != DRV_HAL_OK)
		{
			return drv_mpu6050_device_invalid;
		}

		if (id_value != DRV_MPU6050_I_AM){
			return drv_mpu6050_device_invalid;
		}

		/* Wakeup DRV_MPU6050 */

		/* Format array to send */
		config_data[0] = DRV_MPU6050_PWR_MGMT_1;
		config_data[1] = 0x00;
		/* Try to transmit via I2C */
		if (drv_hal_i2c_master_transmit(handler->drv_instance, handler->address, config_data, 2, I2C_TIMEOUT_MS) != DRV_HAL_OK)
		{
			return drv_mpu6050_error;
		}

		s_initialied_dev_mask |= (1<<dev_number);
		return drv_mpu6050_ok;
	}
	else
	{
		handler->address = DRV_MPU6050_I2C_ADDR | (uint8_t)dev_number;
		return drv_mpu6050_ok;
	}
}

drv_mpu6050_result_t drv_mpu6050_set_gyr(drv_mpu6050_t* handler, drv_mpu6050_data_t *data, drv_mpu6050_gyroscope_t gyro_sens)
{
    uint8_t config_data;

    /* Config gyroscope */
    if (drv_hal_i2c_mem_read(handler->drv_instance, handler->address, DRV_MPU6050_GYRO_CONFIG, 1, &config_data, 1, I2C_TIMEOUT_MS) != DRV_HAL_OK)
    {
        return drv_mpu6050_error;
    }

    config_data = (config_data & 0xE7) | (uint8_t)gyro_sens << 3;
    if (drv_hal_i2c_mem_write(handler->drv_instance, handler->address, DRV_MPU6050_GYRO_CONFIG, 1, &config_data, 1, I2C_TIMEOUT_MS) != DRV_HAL_OK)
    {
        return drv_mpu6050_error;
    }

    switch (gyro_sens)
    {
    case drv_mpu6050_gyroscope_250s:
        data->divider = DRV_MPU6050_GYRO_SENS_250;
        break;
    case drv_mpu6050_gyroscope_500s:
        data->divider = DRV_MPU6050_GYRO_SENS_500;
        break;
    case drv_mpu6050_gyroscope_1000s:
        data->divider = DRV_MPU6050_GYRO_SENS_1000;
        break;
    case drv_mpu6050_gyroscope_2000s:
        data->divider = DRV_MPU6050_GYRO_SENS_2000;
    default:
        break;
    }

    /* Return OK */
    return drv_mpu6050_ok;
}

drv_mpu6050_result_t drv_mpu6050_set_acc(drv_mpu6050_t* handler, drv_mpu6050_data_t *data, drv_mpu6050_accelerometer_t acc_sens)
{
    uint8_t config_data;

    /* Config accelerometer */
    if (drv_hal_i2c_mem_read(handler->drv_instance, handler->address, DRV_MPU6050_ACCEL_CONFIG, 1, &config_data, 1, I2C_TIMEOUT_MS) != DRV_HAL_OK)
    {
        return drv_mpu6050_error;
    }
    config_data = (config_data & 0xE7) | (uint8_t)acc_sens << 3;
    if (drv_hal_i2c_mem_write(handler->drv_instance, handler->address, DRV_MPU6050_ACCEL_CONFIG, 1, &config_data, 1, I2C_TIMEOUT_MS) != DRV_HAL_OK)
    {
        return drv_mpu6050_error;
    }

    /* Set sensitivities for multipling gyro and accelerometer data */
    switch (acc_sens)
    {
    case drv_mpu6050_accelerometer_2g:
        data->divider = DRV_MPU6050_ACCE_SENS_2;
        break;
    case drv_mpu6050_accelerometer_4g:
        data->divider = DRV_MPU6050_ACCE_SENS_4;
        break;
    case drv_mpu6050_accelerometer_8g:
        data->divider = DRV_MPU6050_ACCE_SENS_8;
        break;
    case drv_mpu6050_accelerometer_16g:
        data->divider = DRV_MPU6050_ACCE_SENS_16;
    default:
        break;
    }

    /* Return OK */
    return drv_mpu6050_ok;
}

drv_mpu6050_result_t drv_mpu6050_set_data_rate(drv_mpu6050_t* handler, uint8_t rate)
{
    /* Set data sample rate */
    if (drv_hal_i2c_mem_write(handler->drv_instance, handler->address, DRV_MPU6050_SMPLRT_DIV, 1, &rate, 1, I2C_TIMEOUT_MS) != DRV_HAL_OK)
    {
        return drv_mpu6050_error;
    }

    /* Return OK */
    return drv_mpu6050_ok;
}

drv_mpu6050_result_t drv_mpu6050_set_digital_lp_filter(drv_mpu6050_t* handler, drv_mpu6050_digital_lp_filter_t bandwidth)
{
    /* Set Digital Low Pass Filter bandwidth */
    if (drv_hal_i2c_mem_write(handler->drv_instance, handler->address, DRV_MPU6050_CONFIG, 1, (uint8_t *)&bandwidth, 1, I2C_TIMEOUT_MS) != DRV_HAL_OK)
    {
        return drv_mpu6050_error;
    }

    /* Return OK */
    return drv_mpu6050_ok;
}

drv_mpu6050_result_t drv_mpu6050_enable_interrupts(drv_mpu6050_t* handler)
{
    uint8_t config_data;

    config_data = 0x21;
    /* Enable interrupts for data ready and motion detect */
    if (drv_hal_i2c_mem_write(handler->drv_instance, handler->address, DRV_MPU6050_INT_ENABLE, 1, &config_data, 1, I2C_TIMEOUT_MS) != DRV_HAL_OK)
    {
        return drv_mpu6050_error;
    }

    /* Clear IRQ flag on any read operation */
    if (drv_hal_i2c_mem_read(handler->drv_instance, handler->address, DRV_MPU6050_INT_PIN_CFG, 1, &config_data, 1, I2C_TIMEOUT_MS) != DRV_HAL_OK)
    {
        return drv_mpu6050_error;
    }
    config_data |= 0x10;
    if (drv_hal_i2c_mem_write(handler->drv_instance, handler->address, DRV_MPU6050_INT_PIN_CFG, 1, &config_data, 1, I2C_TIMEOUT_MS) != DRV_HAL_OK)
    {
        return drv_mpu6050_error;
    }

    /* Return OK */
    return drv_mpu6050_ok;
}

drv_mpu6050_result_t drv_mpu6050_disable_interrupts(drv_mpu6050_t* handler)
{
    uint8_t config_data;

    config_data = 0x00;
    /* Disable interrupts */
    if (drv_hal_i2c_mem_write(handler->drv_instance, handler->address, DRV_MPU6050_INT_ENABLE, 1, &config_data, 1, I2C_TIMEOUT_MS) != DRV_HAL_OK)
    {
        return drv_mpu6050_error;
    }

    /* Return OK */
    return drv_mpu6050_ok;
}

drv_mpu6050_result_t drv_mpu6050_read_interrupts(drv_mpu6050_t* handler, drv_mpu6050_interrupt_t* interrupts_struct)
{
    uint8_t read;

    /* Reset structure */
    interrupts_struct->status = 0;

    /* Read interrupts status register */
    if (drv_hal_i2c_mem_read(handler->drv_instance, handler->address, DRV_MPU6050_INT_STATUS, 1, &read, 1, I2C_TIMEOUT_MS) != DRV_HAL_OK)
    {
        return drv_mpu6050_error;
    }

    /* Fill value */
    interrupts_struct->status = read;

    /* Return OK */
    return drv_mpu6050_ok;
}

drv_mpu6050_result_t drv_mpu6050_read_acc(drv_mpu6050_t* handler, drv_mpu6050_data_t *data)
{
    uint8_t raw_data[6];

    /* Read accelerometer data */
    if (drv_hal_i2c_mem_read(handler->drv_instance, handler->address, DRV_MPU6050_ACCEL_XOUT_H, 1, raw_data, 6, I2C_TIMEOUT_MS) != DRV_HAL_OK)
    {
        return drv_mpu6050_error;
    }

    /* Format */
    data->x = (int16_t)(raw_data[0] << 8 | raw_data[1]);
    data->y = (int16_t)(raw_data[2] << 8 | raw_data[3]);
    data->z = (int16_t)(raw_data[4] << 8 | raw_data[5]);

    data->x /= data->divider;
    data->y /= data->divider;
    data->z /= data->divider;

    /* Return OK */
    return drv_mpu6050_ok;
}

drv_mpu6050_result_t drv_mpu6050_read_gyr(drv_mpu6050_t* handler, drv_mpu6050_data_t *data)
{
    uint8_t raw_data[6];

    /* Read gyroscope data */
    if (drv_hal_i2c_mem_read(handler->drv_instance, handler->address, DRV_MPU6050_GYRO_XOUT_H, 1, raw_data, 6, I2C_TIMEOUT_MS) != DRV_HAL_OK)
    {
        return drv_mpu6050_error;
    }

    /* Format */
    data->x = (int16_t)(raw_data[0] << 8 | raw_data[1]);
    data->y = (int16_t)(raw_data[2] << 8 | raw_data[3]);
    data->z = (int16_t)(raw_data[4] << 8 | raw_data[5]);

    data->x /= data->divider;
    data->y /= data->divider;
    data->z /= data->divider;

    /* Return OK */
    return drv_mpu6050_ok;
}

drv_mpu6050_result_t drv_mpu6050_read_temp(drv_mpu6050_t* handler, float *data)
{
    uint8_t raw_data[2];
    int16_t temp;

    /* Read temperature */
    if (drv_hal_i2c_mem_read(handler->drv_instance, handler->address, DRV_MPU6050_TEMP_OUT_H, 1, raw_data, 2, I2C_TIMEOUT_MS) != DRV_HAL_OK)
    {
        return drv_mpu6050_error;
    }

    /* Format temperature */
    temp = (raw_data[0] << 8 | raw_data[1]);
    *data = (float)((int16_t)temp / (float)340.0 + (float)36.53);

    /* Return OK */
    return drv_mpu6050_ok;
}


