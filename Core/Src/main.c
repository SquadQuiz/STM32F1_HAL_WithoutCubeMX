/*
 * main.c
 *
 *  Created on: Dec 5, 2022
 *      Author: Squadkisz
 */

#include "main.h"
#include "rcc.h"
#include "uart.h"
#include "gpio.h"
#include "exti.h"
#include "adc.h"
#include "tim.h"
#include "rtc.h"
#include "spi.h"
#include "rc522.h"
#include "i2c.h"
#include "TJ_MPU6050.h"

int main(void)
{

	HAL_Init();

	//* RCC Peripheral
	rcc_systemClockConfig();

	//* UART Peripheral
	uart_UART1_GPIO_config();
	uart_UART1_config();

	//* GPIO Peripheral
	gpio_LED_config();

	//* I2C Peripheral
	i2c_I2C1_gpio_config();
	i2c_config();
	//* MPU6050 Init
	MPU_ConfigTypeDef mpuConfig;
	mpuConfig.Accel_Full_Scale = AFS_SEL_4g;
	mpuConfig.ClockSource = Internal_8MHz;
	mpuConfig.CONFIG_DLPF = DLPF_184A_188G_Hz;
	mpuConfig.Gyro_Full_Scale = FS_SEL_500;
	mpuConfig.Sleep_Mode_Bit = 0;
	MPU6050_Config(&mpuConfig);

	ScaledData_Def accelScaleDef;

	// Check I2C Slave Address.
	if (HAL_I2C_IsDeviceReady(&i2c1Handle, (0x68 << 1), 5, HAL_MAX_DELAY) == HAL_OK)
	{
		printf("Found MPU6050 I2C Device!\n");
		gpio_LED_writeGreen(1);
	}
	else 
	{
		printf("MPU6050 Device is not Found!\n");
		gpio_LED_writeGreen(0);
	}
	

	while (1)
	{
		MPU6050_Get_Accel_Scale(&accelScaleDef);
		printf("Accel:\nX=%.2f \nY=%.2f \nZ=%.2f\n", accelScaleDef.x, accelScaleDef.y, accelScaleDef.z);
		printf("************************\n\n");
		gpio_LED_toggleGreen();
		HAL_Delay(250);
	}
}

