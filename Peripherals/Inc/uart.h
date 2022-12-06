/*
 * uart.h
 *
 *  Created on: Dec 5, 2022
 *      Author: Squadkisz
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"

//* Import External Variable
extern UART_HandleTypeDef huart1;

/**
 * @brief UART GPIO Configuration
 ** UART1 Tx -> PA9
 ** UART1 Rx -> PA10
 */
void uart_UART1_GPIO_config(void);

/**
 * @brief UART Peripheral Configuration
 */
bool uart_UART1_config(void);

#endif /* INC_UART_H_ */
