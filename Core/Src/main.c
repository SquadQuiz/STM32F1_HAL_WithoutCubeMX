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

	/* Get volume information and free clusters of drive */
	fresult = f_getfree("", &clusterCount, &pFatFs);
	if (fresult != FR_OK) {
		printf("Something wrong, Error code : 0x%02X\n", fresult);
  }

	/* Get total sectors and free sectors */
	totalSpace = (pFatFs->n_fatent - 2) * (pFatFs->csize);
	freeSpace = clusterCount * (pFatFs->csize);

	/* Print the free space (assuming 512 bytes/sector) */
	printf("%10lu KiB total drive space.\n%10lu KiB available.\n", totalSpace / 2, freeSpace / 2);

	// Open file
	fresult = f_open(&fil, "Testfile.txt", FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
	if (fresult != FR_OK) {
		printf("Failed to open file, Error code : 0x%02X\n", fresult);
  }
	else {
		printf("Successfully opened file!\n");
	}

	// Write text file to SD Card
	f_puts("This is HAL library test ...\n", &fil); // don't forget to add \n new line character
	printf("Data is complete written to file\n");

	// Read data back from text file
	f_lseek(&fil, 0); // line seek, this will move file pointer to begin of file
	char readData[50]; // this array for stored string read from file
	UINT readSize = 0; // for stored exactly string data size
	fresult = f_read(&fil, readData, 50, &readSize); // read 50 character from file
		if (fresult != FR_OK) {
		printf("Failed to read file, Error code : 0x%02X\n", fresult);
  }
	else {
		printf("Successfully read file!, size = %d\n", readSize);
	}
	readData[readSize] = 0; // force last character in array to null terminate
	printf("File read content: \n");
	printf(readData); // print data inside the file

	// Close file
	f_close(&fil);

	while (1)
	{
		gpio_LED_toggleGreen();
		HAL_Delay(250);
	}
}
