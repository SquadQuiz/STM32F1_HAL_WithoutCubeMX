/*
 * main.c
 *
 *  Created on: Dec 5, 2022
 *      Author: Squadkisz
 */

#include "main.h"
#include "rcc.h"

int main(void)
{

	HAL_Init();

	rcc_systemClockConfig();

	while(1)
	{

	}

}
