/*
 * i2c.c
 *
 *  Created on: Nov 26, 2023
 *      Author: SquadQuiz
 */

#include "i2c.h"

I2C_HandleTypeDef i2c1Handle;

void i2c_I2C1_gpio_config(void)
{
  GPIO_InitTypeDef gpioInitStruct = {0};
  
  // Enable clock for GPIOB, 
  __HAL_RCC_GPIOB_CLK_ENABLE();

  // PB8 -> I2C SCL (Clock line)
  // PB9 -> I2C SDA (Data line) 
  gpioInitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
  gpioInitStruct.Mode = GPIO_MODE_AF_OD; // Open drain (external pull-up).
  gpioInitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &gpioInitStruct);
  
  // I2C1 remapping default "Re-mapping = 0"
  // PB6 -> I2C SCL (Clock line)
  // PB7 -> I2C SDA (Data line) 
  // So we need to re-map, if want to use PB8, PB9
  __HAL_RCC_AFIO_CLK_ENABLE();
  __HAL_AFIO_REMAP_I2C1_ENABLE(); 
}

bool i2c_config(void)
{
  // Enable clock for I2C1
  __HAL_RCC_I2C1_CLK_ENABLE(); 

  // I2C Handletypdef Initilization.
  i2c1Handle.Instance = I2C1;
  i2c1Handle.Init.ClockSpeed = 100000; // 100kHz Speed (Commonly)
  i2c1Handle.Init.DutyCycle = I2C_DUTYCYCLE_2; // Half-High and Half-Low
  i2c1Handle.Init.OwnAddress1 = 0;
  i2c1Handle.Init.OwnAddress2 = 0;
  i2c1Handle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  i2c1Handle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  i2c1Handle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  i2c1Handle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&i2c1Handle) != HAL_OK) 
  {
    return false;
  }
  return true;
}
