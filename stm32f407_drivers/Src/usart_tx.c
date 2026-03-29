/*
 * usart_tx.c
 *
 *  Created on: Jan 25, 2026
 *      Author: Abijith Radhakrishnan
 */

#include<stdio.h>
#include<string.h>
#include "stm32f407.h"

char msg[1024] = "Abijith on UART tx...\n\r";

USART_Handle_t usart2_handle;

void USART2_Init(void)
{
	usart2_handle.pUSARTx = USART2;
	usart2_handle.USART_Config.USART_Baud = USART_STD_BAUD_115200;
	usart2_handle.USART_Config.USART_HWFlowControl = USART_HW_FLOW_CTRL_NONE;
	usart2_handle.USART_Config.USART_Mode = USART_MODE_ONLY_TX;
	usart2_handle.USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	usart2_handle.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	usart2_handle.USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	USART_Init(&usart2_handle);
}

void 	USART2_GPIOInit(void)
{
	GPIO_Handle_t usart_gpios;


	usart_gpios.pGPIOx = GPIOA;
	usart_gpios.pGPIOx_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	usart_gpios.pGPIOx_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	usart_gpios.pGPIOx_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	usart_gpios.pGPIOx_PinConfig.GPIO_PinAltFunMode = 7;
	usart_gpios. pGPIOx_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//USART2 TX PA2
	usart_gpios.pGPIOx_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_2;
	GPIO_Init(&usart_gpios);


	//USART2 RX
	//Note : PB7
	usart_gpios.pGPIOx_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_3;

	GPIO_Init(&usart_gpios);

}

void GPIO_ButtonInit(void)
{
	GPIO_Handle_t GPIOBtn;

	//this is btn gpio configuration
	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.pGPIOx_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	GPIOBtn.pGPIOx_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	GPIOBtn.pGPIOx_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBtn.pGPIOx_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GPIOBtn);

}

void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}

int main(void)
{

	GPIO_ButtonInit();

	USART2_GPIOInit();

    USART2_Init();

    USART_PeripheralControl(USART2,ENABLE);

    while(1)
    {
		//wait till button is pressed
		while( ! GPIO_ReadFrmInptPin(GPIOA,GPIO_PIN_NO_0) );

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		USART_SendData(&usart2_handle,(uint8_t*)msg,strlen(msg));

    }

	return 0;
}
