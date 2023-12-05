/*
 * rcc.c
 *
 *  Created on: Dec 5, 2022
 *  Last Updated: Jan 21, 2023, Added RTC Clock Configuration.
 *      Author: Squadkisz
 */

#include "rcc.h"

bool rcc_systemClockConfig(void)
{
	/*
	 * Clock Configuration Parameters
	 *
	 * High Speed External Oscillator(HSE) = 8 MHz
	 * -> HSE = 8 MHz
	 *
	 * Phase Lock Loop Multiplier(PLL_MUL) = 9
	 * -> HCLK = (8 MHz * 9) = 72 MHz
	 *
	 * USB Pre-Scaler = 1.5
	 * -> USBCLK = (8 MHz * 1.5) = **48 MHz**
	 *
	 * AHB Pre-Scaler = 1
	 * -> AHBCLK = 72 MHz
	 *
	 * Cortex-Core Pre-Scaler = 1
	 * -> 72 MHz System Clock
	 *
	 * APB1 Pre-Scaler = 2
	 * APB1 Peripheral Clock
	 * -> PCLK1 = (72 MHz * 1/2) = 36 MHz
	 * APB1 Timer Clock
	 * -> APB1_Timer = HCLK = 72 MHz
	 *
	 * APB2 Pre-Scaler = 1
	 * APB2 Peripheral Clock
	 * -> PCLK2 = (72 MHz * 1) = 72 MHz
	 * APB2 Timer Clock
	 * APB2_Timer = HCLK = 72 MHz
	 *
	 * ADC Pre-Scaler = 6
	 * -> ADCCLK = (APB2CLK * ADCPSC) = (72 MHz * 1/6) = 12 MHz
	 * ** ADC Clock Don't Exceed 14 MHz **
	 */

	//? Refers to ClockTree.png

	//* Created Data Structure for Initialize
	RCC_OscInitTypeDef oscInitStruct = {0};
	RCC_ClkInitTypeDef clkInitStruct = {0};
	RCC_PeriphCLKInitTypeDef periphClockInit = {0};

	//* Oscillator Initialization
	oscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE | RCC_OSCILLATORTYPE_LSE; 	// OSC Type -> HSE or LSE
	oscInitStruct.HSEState = RCC_HSE_ON; 										// HSE Clock -> ON
	oscInitStruct.LSEState = RCC_LSE_ON;										// LSE Clock -> ON
	oscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1; 		// Pre-Division = 1
	oscInitStruct.PLL.PLLState = RCC_PLL_ON; 								// PLL -> ON
	oscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;				// PLL -> HSE Source
	oscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9; 								// PLL_MUL = 9, HCLK = 72 MHz

	if(HAL_RCC_OscConfig(&oscInitStruct) != HAL_OK)
	{
		return false;
	}

	//* Clock Initialization
	clkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
													| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2; 	// Use all clock types
	clkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK; 								// System Clock -> PLL Source = (72 MHz)
	clkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1; 												// AHBCLK = SYSCLK/1 = 72 MHz
	clkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2; 												// APB1CLK = HCLK/2 = 36 MHz
	clkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1; 												// APB2CLK = HCLK/1 = 72 MHz
	/*
	 * 0-24 MHz --> 0 Cycle Latency
	 * 24-48 MHz --> 1 Cycle Latency
	 * 48-72 MHz --> 2 Cycle Latency
	*/
	if(HAL_RCC_ClockConfig(&clkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		return false;
	}

	//* Peripheral Clock Configuration
	periphClockInit.PeriphClockSelection = RCC_PERIPHCLK_RTC | RCC_PERIPHCLK_USB;	// Enabled Peripheral clock -> RTC and USB
	periphClockInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;											// RTC Clock -> LSE
	periphClockInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;						  // USB Clk divided from ClkSrc = 72/1.5 = 48MHz
	if(HAL_RCCEx_PeriphCLKConfig(&periphClockInit) != HAL_OK)
	{
		return false;
	}

	return true;
}
