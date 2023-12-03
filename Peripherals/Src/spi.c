/*
 * spi.c
 *
 *  Created on: Nov 25, 2023
 *      Author: SquadQuiz
 */

#include "spi.h"

SPI_HandleTypeDef spi1Handle;

void spi_GPIO_config(void) 
{
  GPIO_InitTypeDef gpioInitStruct = {0};
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  // SPI1 CLK -> PA5
  // SPI1 MOSI -> PA7
  gpioInitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_7;
  gpioInitStruct.Mode = GPIO_MODE_AF_PP;
  gpioInitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  gpioInitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &gpioInitStruct);
  // SPI1 MISO -> PA6
  gpioInitStruct.Pin = GPIO_PIN_6;
  gpioInitStruct.Mode = GPIO_MODE_INPUT;
  gpioInitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  gpioInitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &gpioInitStruct);
  // SPI1 CS1 -> PA4
  gpioInitStruct.Pin = GPIO_PIN_4;
  gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  gpioInitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  gpioInitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &gpioInitStruct);
  // SPIO1 CS2 -> PB1
  gpioInitStruct.Pin = GPIO_PIN_1;
  gpioInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  gpioInitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  gpioInitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &gpioInitStruct);
}

bool spi_config(void)
{
  __HAL_RCC_SPI1_CLK_ENABLE();
  
  spi1Handle.Instance = SPI1;
  spi1Handle.Init.Mode = SPI_MODE_MASTER;
  spi1Handle.Init.Direction = SPI_DIRECTION_2LINES;
  spi1Handle.Init.DataSize = SPI_DATASIZE_8BIT;
  spi1Handle.Init.CLKPolarity = SPI_POLARITY_LOW; // Idle clock 'Low'
  spi1Handle.Init.CLKPhase = SPI_PHASE_1EDGE;
  spi1Handle.Init.NSS = SPI_NSS_SOFT; // Chip select by software
  spi1Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16; // Fclk=72Mhz -> 2 MHz
  spi1Handle.Init.FirstBit = SPI_FIRSTBIT_MSB;
  spi1Handle.Init.TIMode = SPI_TIMODE_DISABLE;
  spi1Handle.Init.CRCPolynomial = SPI_CRCCALCULATION_DISABLE;
  if (HAL_SPI_Init(&spi1Handle) != HAL_OK) 
  {
    return false;
  }
  return true;
}

void spi_CS1_enable(void)
{
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); // Active Low
}

void spi_CS1_disable(void)
{
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
}

void spi_CS2_enable(void)
{
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET); // Active Low
}

void spi_CS2_disable(void)
{
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET); 
}

