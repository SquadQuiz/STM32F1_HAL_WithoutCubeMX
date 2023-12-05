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

#define KB 1024U
#define MB 1048576UL

//SD Card Type -> exFAT, 32 GB
// ..... FAT32
FATFS fs, *pFatFs;
FRESULT fresult;
FIL fil;

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
	gpio_PB_config();

	//* SPI Peripheral
	spi_GPIO_config();
	spi_config();
	//* FatFs
	MX_FATFS_Init();

	// Mount SD Card
	f_mount(&fs, "", 1);
	if (fresult != FR_OK)
	{
		printf("Failed to mount SD Card!!\n");
	}
	else
	{
		printf("Successfully mounted SD Card\n");
	}

	// SD Card Driver Size
	uint32_t blockSize;
	uint32_t numBlocks;
	sd_driver_getSizeInfo(&blockSize, &numBlocks);
	uint64_t totalSize;
	totalSize = (uint64_t)numBlocks * (uint64_t)blockSize / (uint64_t)(KB) ; 
	printf("Total SD Card Size = %llu KiB\n", totalSize);
	printf("Total SD Card Size = %llu MiB\n", totalSize / KB);
	printf("Total SD Card Size = %llu GiB\n", totalSize / MB);

	//FatFs Lib
	// FATFS* pFatFs;
	DWORD clusterCount;
	uint32_t totalSpace, freeSpace;

	/* Get volume information and free clusters of drive 1 */
	fresult = f_getfree("", &clusterCount, &pFatFs);
	if (fresult != FR_OK) {
		printf("Something wrong, Error code : 0x%02X\n", fresult);
  }

	/* Get total sectors and free sectors */
	totalSpace = (pFatFs->n_fatent - 2) * (pFatFs->csize);
	freeSpace = clusterCount * (pFatFs->csize);

	/* Print the free space (assuming 512 bytes/sector) */
	printf("%10lu KiB total drive space.\n%10lu KiB available.\n", totalSpace / 2, freeSpace / 2);

	while (1)
	{
		gpio_LED_toggleGreen();
		HAL_Delay(250);
	}
}
