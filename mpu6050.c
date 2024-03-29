#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "mpu6050.h"

#define MPU6050_SELF_TEST_X         0x0D        /*!< SELF TEST REGISTERS */
#define MPU6050_SELF_TEST_Y         0x0E
#define MPU6050_SELF_TEST_Z         0x0F
#define MPU6050_SELF_TEST_A         0x10
#define MPU6050_SMPLRT_DIV          0x19        /*!< Sample rate diveider */
#define MPU6050_CONFIG              0x1A        /*!< Configuration */
#define MPU6050_GYRO_CONFIG         0x1B        /*!< Gyroscope configuration */
#define MPU6050_ACCEL_CONFIG        0x1C        /*!< Accelerometer configuration */
#define MPU6050_FIFO_EN             0x23        /*!< FIFO enable */
#define MPU6050_I2C_MST_CTRL        0x24        /*!< I2C master control */
#define MPU6050_I2C_SLV0_ADDR       0x25        /*!< I2C slave 0 control */
#define MPU6050_I2C_SLV0_REG        0x26
#define MPU6050_I2C_SLV0_CTRL       0x27
#define MPU6050_I2C_SLV1_ADDR       0x28        /*!< I2C slave 1 control  */
#define MPU6050_I2C_SLV1_REG        0x29
#define MPU6050_I2C_SLV1_CTRL       0x2A
#define MPU6050_I2C_SLV2_ADDR       0x2B        /*!< I2C slave 2 control */
#define MPU6050_I2C_SLV2_REG        0x2C
#define MPU6050_I2C_SLV2_CTRL       0x2D
#define MPU6050_I2C_SLV3_ADDR       0x2E        /*!< I2C slave 3 control */
#define MPU6050_I2C_SLV3_REG        0x2F
#define MPU6050_I2C_SLV3_CTRL       0x30
#define MPU6050_I2C_SLV4_ADDR       0x31        /*!< I2C slave 4 control */
#define MPU6050_I2C_SLV4_REG        0x32
#define MPU6050_I2C_SLV4_DO         0x33
#define MPU6050_I2C_SLV4_CTRL       0x34
#define MPU6050_I2C_SLV4_DI         0x35
#define MPU6050_I2C_MST_STATUS      0x36        /*!< I2C master status */
#define MPU6050_INT_PIN_CFG         0x37        /*!< I2C interrupt pin/bypass enable configuration */
#define MPU6050_INT_ENABLE          0x38        /*!< Interrupt enable */
#define MPU6050_INT_STATUS          0x3A        /*!< Interrupt status */
#define MPU6050_ACCEL_XOUT_H        0x3B        /*!< Accelerometer measurements */
#define MPU6050_ACCEL_XOUT_L        0x3C
#define MPU6050_ACCEL_YOUT_H        0x3D
#define MPU6050_ACCEL_YOUT_L        0x3E
#define MPU6050_ACCEL_ZOUT_H        0x3F
#define MPU6050_ACCEL_ZOUT_L        0x40
#define MPU6050_TEMP_OUT_H          0x41        /*!< Temperature measurements */
#define MPU6050_TEMP_OUT_L          0x42
#define MPU6050_GYRO_XOUT_H         0x43        /*!< Gyroscope measurements */
#define MPU6050_GYRO_XOUT_L         0x44
#define MPU6050_GYRO_YOUT_H         0x45
#define MPU6050_GYRO_YOUT_L         0x46
#define MPU6050_GYRO_ZOUT_H         0x47
#define MPU6050_GYRO_ZOUT_L         0x48
#define MPU6050_EXT_SENS_DATA_00    0x49        /*!< External sensor data */
#define MPU6050_EXT_SENS_DATA_01    0x4A
#define MPU6050_EXT_SENS_DATA_02    0x4B
#define MPU6050_EXT_SENS_DATA_03    0x4C
#define MPU6050_EXT_SENS_DATA_04    0x4D
#define MPU6050_EXT_SENS_DATA_05    0x4E
#define MPU6050_EXT_SENS_DATA_06    0x4F
#define MPU6050_EXT_SENS_DATA_07    0x50
#define MPU6050_EXT_SENS_DATA_08    0x51
#define MPU6050_EXT_SENS_DATA_09    0x52
#define MPU6050_EXT_SENS_DATA_10    0x53
#define MPU6050_EXT_SENS_DATA_11    0x54
#define MPU6050_EXT_SENS_DATA_12    0x55
#define MPU6050_EXT_SENS_DATA_13    0x56
#define MPU6050_EXT_SENS_DATA_14    0x57
#define MPU6050_EXT_SENS_DATA_15    0x58
#define MPU6050_EXT_SENS_DATA_16    0x59
#define MPU6050_EXT_SENS_DATA_17    0x5A
#define MPU6050_EXT_SENS_DATA_18    0x5B
#define MPU6050_EXT_SENS_DATA_19    0x5C
#define MPU6050_EXT_SENS_DATA_20    0x5D
#define MPU6050_EXT_SENS_DATA_21    0x5E
#define MPU6050_EXT_SENS_DATA_22    0x5F
#define MPU6050_EXT_SENS_DATA_23    0x60
#define MPU6050_I2C_SLV0_D0         0x63        /*!< I2C slave 0 data out */
#define MPU6050_I2C_SLV1_D0         0x64        /*!< I2C slave 1 data out */
#define MPU6050_I2C_SLV2_D0         0x65        /*!< I2C slave 2 data out */
#define MPU6050_I2C_SLV3_D0         0x66        /*!< I2C slave 3 data out */
#define MPU6050_I2C_MST_DELAY_CTRL  0x67        /*!< I2C master delay control */
#define MPU6050_SIGNAL_PATH_RESET   0x68        /*!< Signal path reset */
#define MPU6050_USER_CTRL           0x6A        /*!< User control */
#define MPU6050_PWR_MGMT_1          0x6B        /*!< Power management 1 */
#define MPU6050_PWR_MGMT_2          0x6C        /*!< Power management 2 */
#define MPU6050_FIFO_COUNTH         0x72        /*!< FIFO counter registers */
#define MPU6050_FIRO_COUNTL         0x73
#define MPU6050_FIRO_R_W            0x74        /*!< FIFO read write */
#define MPU6050_WHO_AM_I            0x75        /*!< Who am I */
#define MPU6050_ADDR                (0x68<<1)   /*!< MPU6050 Address */

#define BUFFER_CALIB_DEFAULT        1000        /*!< Default the number of sample data when calibrate */


typedef struct mpu6050 {
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
	mpu6050_func_i2c_send       i2c_send;        			/*!< MPU6050 send bytes */
	mpu6050_func_i2c_recv       i2c_recv;         			/*!< MPU6050 receive bytes */
	mpu6050_func_delay          delay;                 		/*!< MPU6050 delay function */
	float                   	accel_scaling_factor;   	/*!< MPU6050 accelerometer scaling factor */
	float                   	gyro_scaling_factor;    	/*!< MPU6050 gyroscope scaling factor */
} mpu6050_t;

mpu6050_handle_t mpu6050_init(void)
{
	mpu6050_handle_t handle = calloc(1, sizeof(mpu6050_t));
	if (handle == NULL)
	{
		return NULL;
	}

	return handle;
}

err_code_t mpu6050_set_config(mpu6050_handle_t handle, mpu6050_cfg_t config)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	float accel_scaling_factor;
	float gyro_scaling_factor;

	/* Update accelerometer scaling factor */
	switch (config.afs_sel)
	{
	case MPU6050_AFS_SEL_2G:
		accel_scaling_factor = (2.0f / 32768.0f);
		break;

	case MPU6050_AFS_SEL_4G:
		accel_scaling_factor = (4.0f / 32768.0f);
		break;

	case MPU6050_AFS_SEL_8G:
		accel_scaling_factor = (8.0f / 32768.0f);
		break;

	case MPU6050_AFS_SEL_16G:
		accel_scaling_factor = (16.0f / 32768.0f);
		break;

	default:
		break;
	}

	/* Update gyroscope scaling factor */
	switch (config.gfs_sel)
	{
	case MPU6050_GFS_SEL_250:
		gyro_scaling_factor = 250.0f / 32768.0f;
		break;

	case MPU6050_GFS_SEL_500:
		gyro_scaling_factor = 500.0f / 32768.0f;
		break;

	case MPU6050_GFS_SEL_1000:
		gyro_scaling_factor = 1000.0f / 32768.0f;
		break;

	case MPU6050_GFS_SEL_2000:
		gyro_scaling_factor = 2000.0f / 32768.0f;
		break;

	default:
		break;
	}

	handle->clksel = config.clksel;
	handle->dlpf_cfg = config.dlpf_cfg;
	handle->sleep_mode = config.sleep_mode;
	handle->gfs_sel = config.gfs_sel;
	handle->afs_sel = config.afs_sel;
	handle->accel_bias_x = config.accel_bias_x;
	handle->accel_bias_y = config.accel_bias_y;
	handle->accel_bias_z = config.accel_bias_z;
	handle->gyro_bias_x = config.gyro_bias_x;
	handle->gyro_bias_y = config.gyro_bias_y;
	handle->gyro_bias_z = config.gyro_bias_z;
	handle->i2c_send = config.i2c_send;
	handle->i2c_recv = config.i2c_recv;
	handle->delay = config.delay;
	handle->accel_scaling_factor = accel_scaling_factor;
	handle->gyro_scaling_factor = gyro_scaling_factor;

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_config(mpu6050_handle_t handle)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	/* Reset MPU6050 */
	uint8_t buffer = 0;
	buffer = 0x80;
	handle->i2c_send(MPU6050_PWR_MGMT_1, &buffer, 1);
	handle->delay(10);

	/* Configure clock source and sleep mode */
	buffer = 0;
	buffer = handle->clksel & 0x07;
	buffer |= (handle->sleep_mode << 6) & 0x40;
	handle->i2c_send(MPU6050_PWR_MGMT_1, &buffer, 1);
	handle->delay(10);

	/* Configure digital low pass filter */
	buffer = 0;
	buffer = handle->dlpf_cfg & 0x07;
	handle->i2c_send(MPU6050_CONFIG, &buffer, 1);

	/* Configure gyroscope range */
	buffer = 0;
	buffer = (handle->gfs_sel << 3) & 0x18;
	handle->i2c_send(MPU6050_GYRO_CONFIG, &buffer, 1);

	/* Configure accelerometer range */
	buffer = 0;
	buffer = (handle->afs_sel << 3) & 0x18;
	handle->i2c_send(MPU6050_ACCEL_CONFIG, &buffer, 1);

	/* Configure sample rate divider */
	buffer = 0;
	buffer = 0x04;
	handle->i2c_send(MPU6050_SMPLRT_DIV, &buffer, 1);

	/* Configure interrupt and enable bypass.
	 * Set Interrupt pin active high, push-pull, Clear and read of INT_STATUS,
	 * enable I2C_BYPASS_EN in INT_PIN_CFG register so additional chips can
	 * join the I2C bus and can be controlled by master.
	 */
	buffer = 0x22;
	handle->i2c_send(MPU6050_INT_PIN_CFG, &buffer, 1);

	buffer = 0x01;
	handle->i2c_send(MPU6050_INT_ENABLE, &buffer, 1);

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_get_accel_raw(mpu6050_handle_t handle, int16_t *raw_x, int16_t *raw_y, int16_t *raw_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (raw_x == NULL) || (raw_y == NULL) || (raw_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	uint8_t accel_raw_data[6];
	handle->i2c_recv(MPU6050_ACCEL_XOUT_H, accel_raw_data, 6);

	*raw_x = (int16_t)((accel_raw_data[0] << 8) + accel_raw_data[1]);
	*raw_y = (int16_t)((accel_raw_data[2] << 8) + accel_raw_data[3]);
	*raw_z = (int16_t)((accel_raw_data[4] << 8) + accel_raw_data[5]);

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_get_accel_calib(mpu6050_handle_t handle, int16_t *calib_x, int16_t *calib_y, int16_t *calib_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (calib_x == NULL) || (calib_y == NULL) || (calib_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	uint8_t accel_raw_data[6];
	handle->i2c_recv(MPU6050_ACCEL_XOUT_H, accel_raw_data, 6);

	*calib_x = (int16_t)((accel_raw_data[0] << 8) + accel_raw_data[1]) - handle->accel_bias_x;
	*calib_y = (int16_t)((accel_raw_data[2] << 8) + accel_raw_data[3]) - handle->accel_bias_y;
	*calib_z = (int16_t)((accel_raw_data[4] << 8) + accel_raw_data[5]) - handle->accel_bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_get_accel_scale(mpu6050_handle_t handle, float *scale_x, float *scale_y, float *scale_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (scale_x == NULL) || (scale_y == NULL) || (scale_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	uint8_t accel_raw_data[6];
	handle->i2c_recv(MPU6050_ACCEL_XOUT_H, accel_raw_data, 6);

	*scale_x = (float)((int16_t)((accel_raw_data[0] << 8) + accel_raw_data[1]) - handle->accel_bias_x) * handle->accel_scaling_factor;
	*scale_y = (float)((int16_t)((accel_raw_data[2] << 8) + accel_raw_data[3]) - handle->accel_bias_y) * handle->accel_scaling_factor;
	*scale_z = (float)((int16_t)((accel_raw_data[4] << 8) + accel_raw_data[5]) - handle->accel_bias_z) * handle->accel_scaling_factor;

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_get_gyro_raw(mpu6050_handle_t handle, int16_t *raw_x, int16_t *raw_y, int16_t *raw_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (raw_x == NULL) || (raw_y == NULL) || (raw_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	uint8_t gyro_raw_data[6];
	handle->i2c_recv(MPU6050_GYRO_XOUT_H, gyro_raw_data, 6);

	*raw_x = (int16_t)((gyro_raw_data[0] << 8) + gyro_raw_data[1]);
	*raw_y = (int16_t)((gyro_raw_data[2] << 8) + gyro_raw_data[3]);
	*raw_z = (int16_t)((gyro_raw_data[4] << 8) + gyro_raw_data[5]);

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_get_gyro_calib(mpu6050_handle_t handle, int16_t *calib_x, int16_t *calib_y, int16_t *calib_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (calib_x == NULL) || (calib_y == NULL) || (calib_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	uint8_t gyro_raw_data[6];
	handle->i2c_recv(MPU6050_GYRO_XOUT_H, gyro_raw_data, 6);

	*calib_x = (int16_t)((gyro_raw_data[0] << 8) + gyro_raw_data[1]) - handle->gyro_bias_x;
	*calib_y = (int16_t)((gyro_raw_data[2] << 8) + gyro_raw_data[3]) - handle->gyro_bias_y;
	*calib_z = (int16_t)((gyro_raw_data[4] << 8) + gyro_raw_data[5]) - handle->gyro_bias_z;


	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_get_gyro_scale(mpu6050_handle_t handle, float *scale_x, float *scale_y, float *scale_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (scale_x == NULL) || (scale_y == NULL) || (scale_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	uint8_t gyro_raw_data[6];
	handle->i2c_recv(MPU6050_GYRO_XOUT_H, gyro_raw_data, 6);

	*scale_x = (float)((int16_t)((gyro_raw_data[0] << 8) + gyro_raw_data[1]) - handle->gyro_bias_x) * handle->gyro_scaling_factor;
	*scale_y = (float)((int16_t)((gyro_raw_data[2] << 8) + gyro_raw_data[3]) - handle->gyro_bias_y) * handle->gyro_scaling_factor;
	*scale_z = (float)((int16_t)((gyro_raw_data[4] << 8) + gyro_raw_data[5]) - handle->gyro_bias_z) * handle->gyro_scaling_factor;

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_set_accel_bias(mpu6050_handle_t handle, int16_t bias_x, int16_t bias_y, int16_t bias_z)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	handle->accel_bias_x = bias_x;
	handle->accel_bias_y = bias_y;
	handle->accel_bias_z = bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_set_gyro_bias(mpu6050_handle_t handle, int16_t bias_x, int16_t bias_y, int16_t bias_z)
{
	/* Check if handle structure is NULL */
	if (handle == NULL)
	{
		return ERR_CODE_NULL_PTR;
	}

	handle->gyro_bias_x = bias_x;
	handle->gyro_bias_y = bias_y;
	handle->gyro_bias_z = bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_get_accel_bias(mpu6050_handle_t handle, int16_t *bias_x, int16_t *bias_y, int16_t *bias_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (bias_x == NULL) || (bias_y == NULL) || (bias_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	*bias_x = handle->accel_bias_x;
	*bias_y = handle->accel_bias_y;
	*bias_z = handle->accel_bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_get_gyro_bias(mpu6050_handle_t handle, int16_t *bias_x, int16_t *bias_y, int16_t *bias_z)
{
	/* Check if handle structure or pointer data is NULL */
	if ((handle == NULL) || (bias_x == NULL) || (bias_y == NULL) || (bias_z == NULL))
	{
		return ERR_CODE_NULL_PTR;
	}

	*bias_x = handle->gyro_bias_x;
	*bias_y = handle->gyro_bias_y;
	*bias_z = handle->gyro_bias_z;

	return ERR_CODE_SUCCESS;
}

err_code_t mpu6050_auto_calib(mpu6050_handle_t handle)
{
	int buffersize = BUFFER_CALIB_DEFAULT;
	int mean_ax, mean_ay, mean_az, mean_gx, mean_gy, mean_gz;
	long i = 0, buff_ax = 0, buff_ay = 0, buff_az = 0, buff_gx = 0, buff_gy = 0, buff_gz = 0;

	while (i < (buffersize + 101))                  /*!< Dismiss 100 first value */
	{
		int16_t accel_raw_x, accel_raw_y, accel_raw_z;
		int16_t gyro_raw_x, gyro_raw_y, gyro_raw_z;

		mpu6050_get_accel_raw(handle, &accel_raw_x, &accel_raw_y, &accel_raw_z);
		mpu6050_get_gyro_raw(handle, &gyro_raw_x, &gyro_raw_y, &gyro_raw_z);

		if (i > 100 && i <= (buffersize + 100))
		{
			buff_ax += accel_raw_x;
			buff_ay += accel_raw_y;
			buff_az += accel_raw_z;
			buff_gx += gyro_raw_x;
			buff_gy += gyro_raw_y;
			buff_gz += gyro_raw_z;
		}
		if (i == (buffersize + 100))
		{
			mean_ax = buff_ax / buffersize;
			mean_ay = buff_ay / buffersize;
			mean_az = buff_az / buffersize;
			mean_gx = buff_gx / buffersize;
			mean_gy = buff_gy / buffersize;
			mean_gz = buff_gz / buffersize;
		}
		i++;
	}

	handle->accel_bias_x = mean_ax;
	handle->accel_bias_y = mean_ay;
	handle->accel_bias_z = mean_az - 1.0f / handle->accel_scaling_factor;
	handle->gyro_bias_x = mean_gx;
	handle->gyro_bias_y = mean_gy;
	handle->gyro_bias_z = mean_gz;

	return ERR_CODE_SUCCESS;
}
