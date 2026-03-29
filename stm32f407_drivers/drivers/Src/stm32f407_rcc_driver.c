/*
 * stm32f407_rcc_driver.c
 *
 *  Created on: Jan 25, 2026
 *      Author: Abijith Radhakrishnan
 */

#include "stm32f407_rcc_driver.h"

uint16_t AHB_Prescaler[8] = {2,4,8,16,64,128,256,512};
uint8_t APB_Prescaler[4] = {2,4,8,16};

uint32_t RCC_GetPCLK1Value(void){

	uint32_t pclk1,SystemClck;
	uint8_t clksrc,temp,ahbp,apb1p;
	clksrc = (RCC->CFGR >> 2) & 0x3;
	if(clksrc == 0){
		SystemClck = 16000000;
	}else if(clksrc == 1){
		SystemClck = 8000000;
	}else if(clksrc == 2){
		SystemClck = RCC_GetPLLOutputClock();
	}

	//for ahb
	temp = (RCC->CFGR >> 4 )& 0xF;
	if(temp < 8){
		ahbp = 1;
	}else{
		ahbp = AHB_Prescaler[temp-8];
	}
	//for apb1
	temp = (RCC->CFGR >> 10 )& 0x7;
	if(temp < 4){
		apb1p = 1;
	}else{
		apb1p = APB_Prescaler[temp-4];
	}
	pclk1 = (SystemClck / ahbp) / apb1p;

	return pclk1;

}

uint32_t RCC_GetPCLK2Value(void)
{
	uint32_t SystemClock=0,tmp,pclk2;
	uint8_t clk_src = ( RCC->CFGR >> 2) & 0X3;

	uint8_t ahbp,apb2p;

	if(clk_src == 0)
	{
		SystemClock = 16000000;
	}else
	{
		SystemClock = 8000000;
	}
	tmp = (RCC->CFGR >> 4 ) & 0xF;

	if(tmp < 0x08)
	{
		ahbp = 1;
	}else
	{
       ahbp = AHB_Prescaler[tmp-8];
	}

	tmp = (RCC->CFGR >> 13 ) & 0x7;
	if(tmp < 0x04)
	{
		apb2p = 1;
	}else
	{
		apb2p = APB_Prescaler[tmp-4];
	}

	pclk2 = (SystemClock / ahbp )/ apb2p;

	return pclk2;
}

uint32_t  RCC_GetPLLOutputClock()
{

	return 0;
}
