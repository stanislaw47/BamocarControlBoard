
/* LICENSE */

#ifndef DRV_HAL_H_
#define DRV_HAL_H_

#include "app_config.h"
#include "i2c.h"

#define I2C_INSTANCE &hi2c2

typedef enum
{
    DRV_HAL_OK       = 0x00U,
    DRV_HAL_ERROR    = 0x01U,
    DRV_HAL_BUSY     = 0x02U,
    DRV_HAL_TIMEOUT  = 0x03U
}drv_hal_status_t;

void *drv_hal_i2c_init(void);
drv_hal_status_t drv_hal_i2c_is_dev_ready(void *drv_instance, uint16_t dev_address, uint32_t timeout);
drv_hal_status_t drv_hal_i2c_mem_read(void *drv_instance, uint16_t dev_address, uint16_t mem_address, uint16_t mem_addr_size, uint8_t *data, uint16_t size, uint32_t timeout);
drv_hal_status_t drv_hal_i2c_master_transmit(void *drv_instance, uint16_t dev_address, uint8_t *data, uint16_t size, uint32_t timeout);
drv_hal_status_t drv_hal_i2c_mem_write(void *drv_instance, uint16_t dev_address, uint16_t mem_address, uint16_t mem_addr_size, uint8_t *data, uint16_t size, uint32_t timeout);


#endif /* DRV_HAL_H_ */
