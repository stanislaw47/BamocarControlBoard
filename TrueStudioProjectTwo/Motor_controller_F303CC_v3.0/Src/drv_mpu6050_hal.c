
/* LICENSE */

#include "drv_mpu6050_hal.h"

void * drv_hal_i2c_init(void)
{
	return (void *)I2C_INSTANCE;
}

inline drv_hal_status_t drv_hal_i2c_is_dev_ready(void *drv_instance, uint16_t dev_address, uint32_t timeout)
{
    return HAL_I2C_IsDeviceReady(drv_instance, dev_address, 2, timeout);
}

inline drv_hal_status_t drv_hal_i2c_mem_read(void *drv_instance, uint16_t dev_address, uint16_t mem_address, uint16_t mem_addr_size, uint8_t *data, uint16_t size, uint32_t timeout)
{
    return HAL_I2C_Mem_Read(drv_instance, dev_address, mem_address, mem_addr_size, data, size, timeout);
}

inline drv_hal_status_t drv_hal_i2c_master_transmit(void *drv_instance, uint16_t dev_address, uint8_t *data, uint16_t size, uint32_t timeout)
{
    return HAL_I2C_Master_Transmit(drv_instance, dev_address, data, size, timeout);
}

inline drv_hal_status_t drv_hal_i2c_mem_write(void *drv_instance, uint16_t dev_address, uint16_t mem_address, uint16_t mem_addr_size, uint8_t *data, uint16_t size, uint32_t timeout)
{
    return HAL_I2C_Mem_Write(drv_instance, dev_address, mem_address, mem_addr_size, data, size, timeout);
}

