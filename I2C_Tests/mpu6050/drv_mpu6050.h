
/* LICENSE */

#ifndef DRV_MPU6050_H_
#define DRV_MPU6050_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "inttypes.h"

// Gyroscope sensitivities in degrees/s
#define DRV_MPU6050_GYRO_SENS_250       ((float) 131 )
#define DRV_MPU6050_GYRO_SENS_500       ((float) 65.5)
#define DRV_MPU6050_GYRO_SENS_1000      ((float) 32.8)
#define DRV_MPU6050_GYRO_SENS_2000      ((float) 16.4)

// Accelerometer sensitivities in g/s
#define DRV_MPU6050_ACCE_SENS_2         ((float) 16384)
#define DRV_MPU6050_ACCE_SENS_4         ((float) 8192 )
#define DRV_MPU6050_ACCE_SENS_8         ((float) 4096 )
#define DRV_MPU6050_ACCE_SENS_16        ((float) 2048 )

/**
 * @brief  Data rates
 */
typedef enum
{
	drv_mpu6050_data_rate_8khz	= 0,		/*!< Sample rate set to 8 kHz  */
	drv_mpu6050_data_rate_4khz  = 1,		/*!< Sample rate set to 4 kHz  */
	drv_mpu6050_data_rate_2khz  = 2,		/*!< Sample rate set to 2 kHz  */
	drv_mpu6050_data_rate_1khz  = 7,		/*!< Sample rate set to 1 kHz  */
	drv_mpu6050_data_rate_500hz = 15,		/*!< Sample rate set to 500 Hz */
	drv_mpu6050_data_rate_250hz = 31,		/*!< Sample rate set to 250 Hz */
	drv_mpu6050_data_rate_125hz = 63,		/*!< Sample rate set to 125 Hz */
	drv_mpu6050_data_rate_100hz = 79		/*!< Sample rate set to 100 Hz */
}drv_mpu6050_data_rate_t;

/**
 * @brief  MPU6050 can have 2 different slave addresses, depends on it's input AD0 pin
 *         This feature allows you to use 2 different sensors with this library at the same time
 */
typedef enum
{
    drv_mpu6050_device_0 = 0x00, 			/*!< AD0 pin is set to low  */
    drv_mpu6050_device_1 = 0x02  			/*!< AD0 pin is set to high */
}drv_mpu6050_device_t;

/**
 * @brief  MPU6050 result enumeration
 */
typedef enum
{
    drv_mpu6050_ok = 0x00,            		/*!< Everything OK */
    drv_mpu6050_error,                		/*!< Unknown error */
    drv_mpu6050_device_not_connected, 		/*!< There is no device with valid slave address  */
    drv_mpu6050_device_invalid        		/*!< Connected device with address is not MPU6050 */
}drv_mpu6050_result_t;

/**
 * @brief  Parameters for accelerometer range
 */
typedef enum
{
    drv_mpu6050_accelerometer_2g  = 0x00,	/*!< Range is +- 2G  */
    drv_mpu6050_accelerometer_4g  = 0x01, 	/*!< Range is +- 4G  */
    drv_mpu6050_accelerometer_8g  = 0x02, 	/*!< Range is +- 8G  */
    drv_mpu6050_accelerometer_16g = 0x03  	/*!< Range is +- 16G */
}drv_mpu6050_accelerometer_t;

/**
 * @brief  Parameters for gyroscope range
 */
typedef enum
{
    drv_mpu6050_gyroscope_250s  = 0x00, 	/*!< Range is +- 250 degrees/s  */
    drv_mpu6050_gyroscope_500s  = 0x01, 	/*!< Range is +- 500 degrees/s  */
    drv_mpu6050_gyroscope_1000s = 0x02, 	/*!< Range is +- 1000 degrees/s */
    drv_mpu6050_gyroscope_2000s = 0x03  	/*!< Range is +- 2000 degrees/s */
} drv_mpu6050_gyroscope_t;

/**
 * @brief  Parameters for low pass filter bandwidth
 */
typedef enum
{
    drv_mpu6050_bandwidth_260Hz = 0,		/* Filter bandwidth is 260Hz */
    drv_mpu6050_bandwidth_184Hz = 1,		/* Filter bandwidth is 184Hz */
    drv_mpu6050_bandwidth_94Hz  = 2,		/* Filter bandwidth is 94Hz  */
    drv_mpu6050_bandwidth_44Hz  = 3,		/* Filter bandwidth is 44Hz  */
    drv_mpu6050_bandwidth_21Hz  = 4,		/* Filter bandwidth is 21Hz  */
    drv_mpu6050_bandwidth_10Hz  = 5,		/* Filter bandwidth is 10Hz  */
    drv_mpu6050_bandwidth_5Hz   = 6			/* Filter bandwidth is 5Hz   */
}drv_mpu6050_digital_lp_filter_t;

/**
 * @brief  Main MPU6050 structure
 */
typedef struct
{
    uint8_t address;
    void    *drv_instance;
}drv_mpu6050_t;

/**
 * @brief  Data from axes structure
 */
typedef struct
{
    float x;
    float y;
    float z;
    float divider;
}drv_mpu6050_data_t;

/**
 * @brief  Interrupts union and structure
 */
typedef union
{
    struct
    {
        uint8_t data_ready:1;       /*!< Data ready interrupt */
        uint8_t reserved2:2;        /*!< Reserved bits */
        uint8_t master:1;           /*!< Master interrupt. Not enabled with library */
        uint8_t fifo_overflow:1;    /*!< FIFO overflow interrupt. Not enabled with library */
        uint8_t reserved1:1;        /*!< Reserved bit */
        uint8_t motion_detection:1; /*!< Motion detected interrupt */
        uint8_t reserved0:1;        /*!< Reserved bit */
    }flag;
    uint8_t status;
} drv_mpu6050_interrupt_t;

/**
 * @brief  Initializes MPU6050 and I2C peripheral
 * @param  *DataStruct: Pointer to empty @ref drv_mpu6050_t structure
 * @param  DeviceNumber: MPU6050 has one pin, AD0 which can be used to set address of device.
 *          This feature allows you to use 2 different sensors on the same board with same library.
 *          If you set AD0 pin to low, then this parameter should be drv_mpu6050_Device_0,
 *          but if AD0 pin is high, then you should use drv_mpu6050_Device_1
 *
 *          Parameter can be a value of @ref drv_mpu6050_Device_t enumeration
 * @param  AccelerometerSensitivity: Set accelerometer sensitivity. This parameter can be a value of @ref drv_mpu6050_Accelerometer_t enumeration
 * @param  GyroscopeSensitivity: Set gyroscope sensitivity. This parameter can be a value of @ref drv_mpu6050_Gyroscope_t enumeration
 * @retval Initialization status:
 *            - drv_mpu6050_result_t: Everything OK
 *            - Other member: in other cases
 */
drv_mpu6050_result_t drv_mpu6050_init(drv_mpu6050_t* data_struct, drv_mpu6050_device_t dev_number);

/**
 * @brief  Sets gyroscope sensitivity
 * @param  *DataStruct: Pointer to @ref drv_mpu6050_t structure indicating MPU6050 device
 * @param  GyroscopeSensitivity: Gyro sensitivity value. This parameter can be a value of @ref drv_mpu6050_Gyroscope_t enumeration
 * @retval Member of @ref drv_mpu6050_result_t enumeration
 */
drv_mpu6050_result_t drv_mpu6050_set_gyr(drv_mpu6050_t* handler, drv_mpu6050_data_t *data, drv_mpu6050_gyroscope_t gyro_sens);

/**
 * @brief  Sets accelerometer sensitivity
 * @param  *DataStruct: Pointer to @ref drv_mpu6050_t structure indicating MPU6050 device
 * @param  AccelerometerSensitivity: Gyro sensitivity value. This parameter can be a value of @ref drv_mpu6050_Accelerometer_t enumeration
 * @retval Member of @ref drv_mpu6050_result_t enumeration
 */
drv_mpu6050_result_t drv_mpu6050_set_acc(drv_mpu6050_t* handler, drv_mpu6050_data_t *data, drv_mpu6050_accelerometer_t acc_sens);

/**
 * @brief  Sets output data rate
 * @param  *DataStruct: Pointer to @ref drv_mpu6050_t structure indicating MPU6050 device
 * @param  rate: Data rate value. An 8-bit value for prescaler value
 * @retval Member of @ref drv_mpu6050_result_t enumeration
 */
drv_mpu6050_result_t drv_mpu6050_set_data_rate(drv_mpu6050_t* data_struct, drv_mpu6050_data_rate_t data_rate);

/**
 * @brief  Sets digital low pass filter bandwidth
 * @param  *DataStruct: Pointer to @ref drv_mpu6050_t structure indicating MPU6050 device
 * @param  Bandwidth: drv_mpu6050_DigitalLowPassFilter_t value.
 * @retval Member of @ref drv_mpu6050_result_t enumeration
 */
drv_mpu6050_result_t drv_mpu6050_set_digital_lp_filter(drv_mpu6050_t* data_struct, drv_mpu6050_digital_lp_filter_t bandwidth);

/**
 * @brief  Enables interrupts
 * @param  *DataStruct: Pointer to @ref drv_mpu6050_t structure indicating MPU6050 device
 * @retval Member of @ref drv_mpu6050_result_t enumeration
 */
drv_mpu6050_result_t drv_mpu6050_enable_interrupts(drv_mpu6050_t* data_struct);

/**
 * @brief  Disables interrupts
 * @param  *DataStruct: Pointer to @ref drv_mpu6050_t structure indicating MPU6050 device
 * @retval Member of @ref drv_mpu6050_result_t enumeration
 */
drv_mpu6050_result_t drv_mpu6050_disable_interrupts(drv_mpu6050_t* data_struct);

/**
 * @brief  Reads and clears interrupts
 * @param  *DataStruct: Pointer to @ref drv_mpu6050_t structure indicating MPU6050 device
 * @param  *InterruptsStruct: Pointer to @ref drv_mpu6050_Interrupt_t structure to store status in
 * @retval Member of @ref drv_mpu6050_result_t enumeration
 */
drv_mpu6050_result_t drv_mpu6050_read_interrupts(drv_mpu6050_t* data_struct, drv_mpu6050_interrupt_t* interupts_struct);

/**
 * @brief  Reads accelerometer data from sensor
 * @param  *DataStruct: Pointer to @ref drv_mpu6050_t structure to store data to
 * @retval Member of @ref drv_mpu6050_result_t:
 *            - drv_mpu6050_Result_Ok: everything is OK
 *            - Other: in other cases
 */
drv_mpu6050_result_t drv_mpu6050_read_acc(drv_mpu6050_t* handler, drv_mpu6050_data_t *data);

/**
 * @brief  Reads gyroscope data from sensor
 * @param  *DataStruct: Pointer to @ref drv_mpu6050_t structure to store data to
 * @retval Member of @ref drv_mpu6050_result_t:
 *            - drv_mpu6050_Result_Ok: everything is OK
 *            - Other: in other cases
 */
drv_mpu6050_result_t drv_mpu6050_read_gyr(drv_mpu6050_t* handler, drv_mpu6050_data_t *data);

/**
 * @brief  Reads temperature data from sensor
 * @param  *DataStruct: Pointer to @ref drv_mpu6050_t structure to store data to
 * @retval Member of @ref drv_mpu6050_result_t:
 *            - drv_mpu6050_Result_Ok: everything is OK
 *            - Other: in other cases
 */
drv_mpu6050_result_t drv_mpu6050_read_temp(drv_mpu6050_t* handler, float *data);

#ifdef __cplusplus
}
#endif
#endif /* DRV_MPU6050_H_ */
