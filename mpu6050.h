// MIT License

// Copyright (c) 2024 phonght32

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __MPU6050_H__
#define __MPU6050_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "err_code.h"

typedef err_code_t (*mpu6050_func_i2c_recv)(uint8_t *buf_read, uint16_t len, uint32_t timeout_ms);
typedef err_code_t (*mpu6050_func_i2c_send)(uint8_t *buf_send, uint16_t len, uint32_t timeout_ms);
typedef void (*mpu6050_func_delay)(uint32_t ms);

/**
 * @brief   Handle structure.
 */
typedef struct mpu6050 *mpu6050_handle_t;

/**
 * @brief   Clock selection.
 */
typedef enum {
	MPU6050_CLKSEL_INTERNAL_8_MHZ = 0,      /*!< Internal 8 MHz oscillator */
	MPU6050_CLKSEL_X_GYRO_REF,              /*!< PLL with X axis gyroscope reference */
	MPU6050_CLKSEL_Y_GYRO_REF,              /*!< PLL with Y axis gyroscope reference */
	MPU6050_CLKSEL_Z_GYRO_REF,              /*!< PLL with Z axis gyroscope reference */
	MPU6050_CLKSEL_EXTERNAL_32_768_KHZ,     /*!< PLL with eternal 32.768 KHz reference */
	MPU6050_CLKSEL_EXTERNAL_19_2_MHZ,       /*!< PLL with external 19.2 MHz reference */
	MPU6050_TIM_GEN_RESET = 7,              /*!< Stops the clock and keeps the timing generator in reset */
	MPU6050_CLKSEL_MAX
} mpu6050_clksel_t;

/**
 * @brief   Low pass filter.
 */
typedef enum {
	MPU6050_260ACCEL_256GYRO_BW_HZ = 0,     /*!< 260 Hz accelerometer bandwidth, 256 Hz gyroscope bandwidth */
	MPU6050_184ACCEL_188GYRO_BW_HZ,         /*!< 184 Hz accelerometer bandwidth, 188 Hz gyroscope bandwidth */
	MPU6050_94ACCEL_98GYRO_BW_HZ,           /*!< 94 Hz accelerometer bandwidth, 98 Hz gyroscope bandwidth */
	MPU6050_44ACCEL_42GYRO_BW_HZ,           /*!< 44 Hz accelerometer bandwidth, 42 Hz gyroscope bandwidth */
	MPU6050_21ACCEL_20GYRO_BW_HZ,           /*!< 21 Hz accelerometer bandwidth, 20 Hz gyroscope bandwidth */
	MPU6050_10ACCEL_10GYRO_BW_HZ,           /*!< 10 Hz accelerometer bandwidth, 10 Hz gyroscope bandwidth */
	MPU6050_5ACCEL_5GYRO_BW_HZ,             /*!< 5 Hz accelerometer bandwidth, 5 Hz gyroscope bandwidth */
	MPU6050_DLPF_CFG_MAX
} mpu6050_dlpf_cfg_t;

/**
 * @brief   Sleep mode.
 */
typedef enum {
	MPU6050_DISABLE_SLEEP_MODE = 0,         /*!< Disable sleep mode */
	MPU6050_LOW_PWR_SLEEP_MODE,             /*!< Low power mode */
	MPU6050_SLEEP_MODE_MAX
} mpu6050_sleep_mode_t;

/**
 * @brief   Gyroscope full scale.
 */
typedef enum {
	MPU6050_GFS_SEL_250 = 0,                /*!< 250 deg/s */
	MPU6050_GFS_SEL_500,                    /*!< 500 deg/s */
	MPU6050_GFS_SEL_1000,                   /*!< 1000 deg/s */
	MPU6050_GFS_SEL_2000,                   /*!< 2000 deg/s */
	MPU6050_GFS_SEL_MAX
} mpu6050_gfs_sel_t;

/**
 * @brief   Accelerometer full scale.
 */
typedef enum {
	MPU6050_AFS_SEL_2G = 0,                 /*!< 2g */
	MPU6050_AFS_SEL_4G,                     /*!< 4g */
	MPU6050_AFS_SEL_8G,                     /*!< 8g */
	MPU6050_AFS_SEL_16G,                    /*!< 16g */
	MPU6050_AFS_SEL_MAX
} mpu6050_afs_sel_t;

/**
 * @brief   Configuration structure.
 */
typedef struct {
	mpu6050_clksel_t        	clksel;         			/*!< MPU6050 clock source */
	mpu6050_dlpf_cfg_t      	dlpf_cfg;       			/*!< MPU6050 digital low pass filter (DLPF) */
	mpu6050_sleep_mode_t    	sleep_mode;     			/*!< MPU6050 sleep mode */
	mpu6050_gfs_sel_t        	gfs_sel;         			/*!< MPU6050 gyroscope full scale range */
	mpu6050_afs_sel_t       	afs_sel;        			/*!< MPU6050 accelerometer full scale range */
	int16_t                     accel_bias_x;               /*!< Accelerometer bias of x axis */
	int16_t                     accel_bias_y;               /*!< Accelerometer bias of y axis */
	int16_t                     accel_bias_z;               /*!< Accelerometer bias of z axis */
	int16_t                     gyro_bias_x;                /*!< Gyroscope bias of x axis */
	int16_t                     gyro_bias_y;                /*!< Gyroscope bias of y axis */
	int16_t                     gyro_bias_z;                /*!< Gyroscope bias of z axis */
	mpu6050_func_i2c_recv       i2c_recv;         			/*!< MPU6050 receive bytes */
	mpu6050_func_i2c_send       i2c_send;        			/*!< MPU6050 send bytes */
	mpu6050_func_delay          delay;                 		/*!< MPU6050 delay function */
} mpu6050_cfg_t;

/*
 * @brief   Initialize MPU6050 with default parameters.
 *
 * @note    This function must be called first.
 *
 * @param   None.
 *
 * @return
 *      - Handle structure: Success.
 *      - Others:           Fail.
 */
mpu6050_handle_t mpu6050_init(void);

/*
 * @brief   Set configuration parameters.
 *
 * @param 	handle Handle structure.
 * @param   config Configuration structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t mpu6050_set_config(mpu6050_handle_t handle, mpu6050_cfg_t config);

/*
 * @brief   Configure MPU6050 to run.
 *
 * @param 	handle Handle structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t mpu6050_config(mpu6050_handle_t handle);

/*
 * @brief   Get accelerometer raw value.
 *
 * @param   handle Handle structure.
 * @param   raw_x Raw value x axis.
 * @param   raw_y Raw value y axis.
 * @param   raw_z Raw value z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t mpu6050_get_accel_raw(mpu6050_handle_t handle, int16_t *raw_x, int16_t *raw_y, int16_t *raw_z);

/*
 * @brief   Get accelerometer calibrated data.
 *
 * @param   handle Handle structure.
 * @param   calib_x Calibrated data x axis.
 * @param   calib_y Calibrated data y axis.
 * @param   calib_z Calibrated data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t mpu6050_get_accel_calib(mpu6050_handle_t handle, int16_t *calib_x, int16_t *calib_y, int16_t *calib_z);

/*
 * @brief   Get accelerometer scaled data.
 *
 * @param   handle Handle structure.
 * @param   scale_x Scaled data x axis.
 * @param   scale_y Scaled data y axis.
 * @param   scale_z Scaled data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t mpu6050_get_accel_scale(mpu6050_handle_t handle, float *scale_x, float *scale_y, float *scale_z);

/*
 * @brief   Get gyroscope raw value.
 *
 * @param   handle Handle structure.
 * @param   raw_x Raw value x axis.
 * @param   raw_y Raw value y axis.
 * @param   raw_z Raw value z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t mpu6050_get_gyro_raw(mpu6050_handle_t handle, int16_t *raw_x, int16_t *raw_y, int16_t *raw_z);

/*
 * @brief   Get gyroscope calibrated data.
 *
 * @param   handle Handle structure.
 * @param   calib_x Calibrated data x axis.
 * @param   calib_y Calibrated data y axis.
 * @param   calib_z Calibrated data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t mpu6050_get_gyro_calib(mpu6050_handle_t handle, int16_t *calib_x, int16_t *calib_y, int16_t *calib_z);

/*
 * @brief   Get gyroscope scaled data.
 *
 * @param   handle Handle structure.
 * @param   scale_x Scaled data x axis.
 * @param   scale_y Scaled data y axis.
 * @param   scale_z Scaled data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t mpu6050_get_gyro_scale(mpu6050_handle_t handle, float *scale_x, float *scale_y, float *scale_z);

/*
 * @brief   Set accelerometer bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_x Bias data x axis.
 * @param   bias_y Bias data y axis.
 * @param   bias_z Bias data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t mpu6050_set_accel_bias(mpu6050_handle_t handle, int16_t bias_x, int16_t bias_y, int16_t bias_z);

/*
 * @brief   Set gyroscope bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_x Bias data x axis.
 * @param   bias_y Bias data y axis.
 * @param   bias_z Bias data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t mpu6050_set_gyro_bias(mpu6050_handle_t handle, int16_t bias_x, int16_t bias_y, int16_t bias_z);

/*
 * @brief   Get accelerometer bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_x Bias data x axis.
 * @param   bias_y Bias data y axis.
 * @param   bias_z Bias data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t mpu6050_get_accel_bias(mpu6050_handle_t handle, int16_t *bias_x, int16_t *bias_y, int16_t *bias_z);

/*
 * @brief   Get gyroscope bias data.
 *
 * @param   handle Handle structure.
 * @param   bias_x Bias data x axis.
 * @param   bias_y Bias data y axis.
 * @param   bias_z Bias data z axis.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t mpu6050_get_gyro_bias(mpu6050_handle_t handle, int16_t *bias_x, int16_t *bias_y, int16_t *bias_z);

/*
 * @brief   Auto calibrate all acceleromter and gyroscope bias value.
 *
 * @param   handle Handle structure.
 *
 * @return
 *      - ERR_CODE_SUCCESS: Success.
 *      - Others:           Fail.
 */
err_code_t mpu6050_auto_calib(mpu6050_handle_t handle);


#ifdef __cplusplus
}
#endif

#endif /* __MPU6050_H__ */