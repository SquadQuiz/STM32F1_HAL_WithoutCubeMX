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
#include "crc.h"
#include "pwr.h"
#include "fatfs.h"
#include "sd_driver.h"
#include "usb_device.h"
// #include "cmsis_os.h" 
#include "wav_recorder.h"

FATFS fs;
FRESULT fresult;

int main(void)
{
	//* HAL Library
	HAL_Init();

	//* RCC Peripheral
	rcc_systemClockConfig();

	//* UART Peripheral
	uart_UART1_GPIO_config();
	uart_UART1_config();

	//* GPIO Peripheral
	gpio_LED_config();
	gpio_PB_config();

	//* SD Card on SPI
	spi_GPIO_config();
	spi_config();
	MX_FATFS_Init();

	fresult = f_mount(&fs, "", 1);
	if (fresult != FR_OK)
	{
		printf("Failed to mount SD Card to FatFs\n");
	}
	else
	{
		printf("Successfully Mounted SD Card\n");
	}

	// ADC
	adc_GPIO_config();
	adc_MIC_config();
	// ADC DMA
	adc_dma_config();
	// TIM3
	tim_TIM3_config(0);

	uint32_t timeout = HAL_GetTick();
	bool recflag = 0;

	while (1)
	{
		HAL_Delay(500);
		if (!recflag)
		{
			// WAV Init
			if (wav_recorder_fileCreate("RECORD.WAV"))
			{
				printf("WAV File created successfully\n");
			}
			else
			{
				printf("File creation failed\n");
			}
			HAL_Delay(1000);
			// Start recording
			wav_recorder_record();
			gpio_LED_writeGreen(1);
			printf("Recording Started\n");
			while(!wav_recorder_isFinished())
			{
				wav_recorder_process();
				if (HAL_GetTick() > timeout + 5000)
				{
					wav_recorder_stop();
					wav_recorder_process();
					printf("Recording Stopped\n");
				}
			}
			gpio_LED_writeGreen(0);
			recflag = 1;
		}
	}
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
	wavRecorder_halfTransfer_Callback();
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	wavRecorder_fullTransfer_Callback();
}

