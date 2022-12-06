/*
 * uart.c
 *
 *  Created on: Dec 5, 2022
 *      Author: Squadkisz
 */

#include "uart.h"

//* UART1 Handle Typedef Global Variable
UART_HandleTypeDef huart1;

/**
 * @brief UART GPIO Configuration
 */
void uart_UART1_GPIO_config(void)
{
	/*
	 * PA9  -> UART_TX
	 * PA10 -> UART_RX
	 */
	
	GPIO_InitTypeDef gpioInitStruct = {0};
	__HAL_RCC_GPIOA_CLK_ENABLE();								// Enable GPIOA Clock

	//* UART GPIO Initialization
	//* PA9 -> UART_TX
	gpioInitStruct.Pin = GPIO_PIN_9; 						 // GPIO PA9
	gpioInitStruct.Mode = GPIO_MODE_AF_PP; 			 // GPIO Alternate function push-pull
	gpioInitStruct.Speed = GPIO_SPEED_FREQ_HIGH; // PinSpeed -> High Speed
	HAL_GPIO_Init(GPIOA, &gpioInitStruct);			 

	//* PA10 -> UART_RX
	gpioInitStruct.Pin = GPIO_PIN_10; 					 // GPIO PA10
	gpioInitStruct.Mode = GPIO_MODE_INPUT; 			 // GPIO As Input-pin
	gpioInitStruct.Pull = GPIO_NOPULL;					 // GPIO No-pull
	//? ignored pin speed for this case.
	HAL_GPIO_Init(GPIOA, &gpioInitStruct); 			 
}

/**
 * @brief UART Peripheral Configuration
 */
bool uart_UART1_config(void)
{
	__HAL_RCC_USART1_CLK_ENABLE(); 									 // Enable UART1 Clock

	//* UART1 Configuration
	huart1.Instance = USART1;												 // huart1 -> USART1
	huart1.Init.BaudRate = 115200;									 // Baudrate = 115200
	huart1.Init.WordLength = UART_WORDLENGTH_8B;		 // Wordlength = 8 Bytes
	huart1.Init.StopBits = UART_STOPBITS_1;					 // Stop bit = 1
	huart1.Init.Parity = UART_PARITY_NONE;					 // Parity = None
	huart1.Init.Mode = UART_MODE_TX_RX;							 // Mode -> Tx,Rx
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;		 // Hardware flow control = None
	huart1.Init.OverSampling = UART_OVERSAMPLING_16; // Oversampling = 16
	if (HAL_UART_Init(&huart1) != HAL_OK)
	{
		return false;
	}

	return true;
}
