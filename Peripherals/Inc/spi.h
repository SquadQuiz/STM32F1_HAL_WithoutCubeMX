/*
 * spi.h
 *
 *  Created on: Nov 25, 2023
 *      Author: SquadQuiz
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_

#include "main.h"

extern SPI_HandleTypeDef spi1Handle;

/**
 * @brief SPI1 GPIO Configuration
 */
void spi_GPIO_config(void);

/**
 * @brief SPI1 peripheral
 */
bool spi_config(void);

/**
 * @brief SPI1 CS1-RFID
 */
void spi_CS1_enable(void);
void spi_CS1_disable(void);

/**
 * @brief SPI1 CS2-SDCARD
 */
void spi_CS2_enable(void);
void spi_CS2_disable(void);

#endif /* INC_SPI_H_ */
