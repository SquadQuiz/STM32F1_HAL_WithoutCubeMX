/*
 * printf_redirect.c
 *
 *  Created on: Dec 5, 2022
 *      Author: Squadkisz
 */

#include "uart.h"

//* Use float with printf form newlib-nano (-u_printf_float)

int __io_putchar(int ch);
int _write(int file, char *ptr, int len);

int __io_putchar(int ch)
{
  uint8_t c[1];
  c[0] = ch & 0x00FF;
  HAL_UART_Transmit(&huart1, &c[0], 1, 100);
  return ch;
}

int _write(int file, char *ptr, int len)
{
  int DataIdx;
  for (DataIdx = 0; DataIdx < len; DataIdx++)
  {
    __io_putchar(*ptr++);
  }
  return len;
}
