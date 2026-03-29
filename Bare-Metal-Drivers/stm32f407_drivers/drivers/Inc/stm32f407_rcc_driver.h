/*
 * stm32f407_rcc_driver.h
 *
 *  Created on: Jan 25, 2026
 *      Author: Abijith Radhakrishnan
 */
#include "stm32f407.h"

#ifndef INC_STM32F407_RCC_DRIVER_H_
#define INC_STM32F407_RCC_DRIVER_H_


uint32_t RCC_GetPCLK1Value(void);
uint32_t RCC_GetPCLK2Value(void);
uint32_t  RCC_GetPLLOutputClock(void);

#endif /* INC_STM32F407_RCC_DRIVER_H_ */
