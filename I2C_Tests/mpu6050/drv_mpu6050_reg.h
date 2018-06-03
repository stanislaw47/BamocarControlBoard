
/* LICENSE */

#ifndef DRV_MPU6050_REG_H_
#define DRV_MPU6050_REG_H_
#ifdef __cplusplus
extern "C" {
#endif

// Default I2C address
#define DRV_MPU6050_I2C_ADDR            ((uint8_t)0xD0)

// Who I am register value
#define DRV_MPU6050_I_AM                ((uint8_t)0x68)

// DRV_MPU6050 registers
#define DRV_MPU6050_AUX_VDDIO           ((uint8_t)0x01)
#define DRV_MPU6050_SMPLRT_DIV          ((uint8_t)0x19)
#define DRV_MPU6050_CONFIG              ((uint8_t)0x1A)
#define DRV_MPU6050_GYRO_CONFIG         ((uint8_t)0x1B)
#define DRV_MPU6050_ACCEL_CONFIG        ((uint8_t)0x1C)
#define DRV_MPU6050_MOTION_THRESH       ((uint8_t)0x1F)
#define DRV_MPU6050_INT_PIN_CFG         ((uint8_t)0x37)
#define DRV_MPU6050_INT_ENABLE          ((uint8_t)0x38)
#define DRV_MPU6050_INT_STATUS          ((uint8_t)0x3A)
#define DRV_MPU6050_ACCEL_XOUT_H        ((uint8_t)0x3B)
#define DRV_MPU6050_ACCEL_XOUT_L        ((uint8_t)0x3C)
#define DRV_MPU6050_ACCEL_YOUT_H        ((uint8_t)0x3D)
#define DRV_MPU6050_ACCEL_YOUT_L        ((uint8_t)0x3E)
#define DRV_MPU6050_ACCEL_ZOUT_H        ((uint8_t)0x3F)
#define DRV_MPU6050_ACCEL_ZOUT_L        ((uint8_t)0x40)
#define DRV_MPU6050_TEMP_OUT_H          ((uint8_t)0x41)
#define DRV_MPU6050_TEMP_OUT_L          ((uint8_t)0x42)
#define DRV_MPU6050_GYRO_XOUT_H         ((uint8_t)0x43)
#define DRV_MPU6050_GYRO_XOUT_L         ((uint8_t)0x44)
#define DRV_MPU6050_GYRO_YOUT_H         ((uint8_t)0x45)
#define DRV_MPU6050_GYRO_YOUT_L         ((uint8_t)0x46)
#define DRV_MPU6050_GYRO_ZOUT_H         ((uint8_t)0x47)
#define DRV_MPU6050_GYRO_ZOUT_L         ((uint8_t)0x48)
#define DRV_MPU6050_MOT_DETECT_STATUS   ((uint8_t)0x61)
#define DRV_MPU6050_SIGNAL_PATH_RESET   ((uint8_t)0x68)
#define DRV_MPU6050_MOT_DETECT_CTRL     ((uint8_t)0x69)
#define DRV_MPU6050_USER_CTRL           ((uint8_t)0x6A)
#define DRV_MPU6050_PWR_MGMT_1          ((uint8_t)0x6B)
#define DRV_MPU6050_PWR_MGMT_2          ((uint8_t)0x6C)
#define DRV_MPU6050_FIFO_COUNTH         ((uint8_t)0x72)
#define DRV_MPU6050_FIFO_COUNTL         ((uint8_t)0x73)
#define DRV_MPU6050_FIFO_R_W            ((uint8_t)0x74)
#define DRV_MPU6050_WHO_AM_I            ((uint8_t)0x75)

#ifdef __cplusplus
}
#endif
#endif /* DRV_MPU6050_REG_H_ */
