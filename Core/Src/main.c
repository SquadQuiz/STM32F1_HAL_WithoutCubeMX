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

bool uartRxFlag = false;
bool uartTxFlag = false;

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
	// gpio_PB_config();
	// gpio_SW_config();

	uint8_t rxBuffer[20];
	uint8_t dmaCount = 0;
	printf("Send 10 bytes please\n");
	HAL_UART_Receive_DMA(&huart1, rxBuffer, 10);

	while (1)
	{
		gpio_LED_toggleGreen();
		HAL_Delay(1000);
		//Check for received.
		dmaCount = __HAL_DMA_GET_COUNTER(&dmaHandle_uart1_rx);
		printf("DMA Count: %d\n", dmaCount);
		if (uartRxFlag) 
		{
			uartRxFlag = false;
			HAL_UART_Transmit_DMA(&huart1, rxBuffer, 10);
			while(!uartTxFlag);
			uartTxFlag = false;
			// Start UART1 reception again.
			printf("Send 10 bytes please\n");
			HAL_UART_Receive_DMA(&huart1, rxBuffer, 10);
		}
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		uartRxFlag = true;
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1)
	{
		uartTxFlag = true;
	}
}
