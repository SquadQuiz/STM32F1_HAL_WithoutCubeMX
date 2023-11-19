/*
 * uart.c
 *
 *  Created on: Dec 5, 2022
 *      Author: Squadkisz
 */

#include "uart.h"

//* Handle Typedef Global Variable
UART_HandleTypeDef huart1;
DMA_HandleTypeDef dmaHandle_uart1_tx;
DMA_HandleTypeDef dmaHandle_uart1_rx;

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

	// DMA Channel 4 --> UART1 Tx
	// DMA Channel 5 --> UART1 Rx

	__HAL_RCC_DMA1_CLK_ENABLE(); // Enable clock for DMA1
	// UART1 DMA Tx Init
	dmaHandle_uart1_tx.Instance = DMA1_Channel4;
	dmaHandle_uart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	dmaHandle_uart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	dmaHandle_uart1_tx.Init.MemInc = DMA_MINC_ENABLE;
	dmaHandle_uart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	dmaHandle_uart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	dmaHandle_uart1_tx.Init.Mode = DMA_NORMAL;
	dmaHandle_uart1_tx.Init.Priority = DMA_PRIORITY_LOW;
	if (HAL_DMA_Init(&dmaHandle_uart1_tx) != HAL_OK)
	{
		return false;
	}
	__HAL_LINKDMA(&huart1, hdmatx, dmaHandle_uart1_tx); // Link/Bind UART Peripheral to DMA notes: "hdmatx" is pointer from DMA_HandleTypeDef 
	HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 5, 0); 		// Set IRQ Priority
	HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);							// Enable DMA1 Channel 4 IRQ

	// UART1 DMA Rx Init
	dmaHandle_uart1_rx.Instance = DMA1_Channel5;
	dmaHandle_uart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	dmaHandle_uart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	dmaHandle_uart1_rx.Init.MemInc = DMA_MINC_ENABLE;
	dmaHandle_uart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	dmaHandle_uart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	dmaHandle_uart1_rx.Init.Mode = DMA_NORMAL;
	dmaHandle_uart1_rx.Init.Priority = DMA_PRIORITY_LOW;
	if (HAL_DMA_Init(&dmaHandle_uart1_rx) != HAL_OK)
	{
		return false;
	}
	__HAL_LINKDMA(&huart1, hdmarx, dmaHandle_uart1_rx); // Link/Bind UART Peripheral to DMA notes: "hdmarx" is pointer from DMA_HandleTypeDef 
	HAL_NVIC_SetPriority(DMA1_Channel5_IRQn, 5, 0); 		// Set IRQ Priority
	HAL_NVIC_EnableIRQ(DMA1_Channel5_IRQn);							// Enable DMA1 Channel 5 IRQ

	// Enable UART IRQ
	HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
	HAL_NVIC_EnableIRQ(USART1_IRQn);

	return true;
}
