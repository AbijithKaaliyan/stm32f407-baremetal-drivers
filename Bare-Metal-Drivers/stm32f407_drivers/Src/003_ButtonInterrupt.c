/*
 * 003_ButtonInterrupt.c
 *
 *  Created on: Oct 25, 2025
 *      Author: Abijith Radhakrishnan
 */

#include "stm32f407.h"
#include<string.h>
#define HIGH 1
#define BTN_PRESSED HIGH

void delay(void){
	//introduces 200ms delay when system clock is 16MHz which we are using here
	for(volatile uint32_t i = 0; i< 500000/2; i++);
}

int main (void) {

	GPIO_Handle_t gpioLed,gpioButton;
	memset(&gpioLed,0,sizeof(gpioLed));
	memset(&gpioButton,0,sizeof(gpioButton));
	gpioLed.pGPIOx = GPIOD; 																		//selecting the port, in this case it is port D where LED is connected
	gpioLed.pGPIOx_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
	gpioLed.pGPIOx_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	gpioLed.pGPIOx_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioLed.pGPIOx_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	gpioLed.pGPIOx_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_PeriClkCtrl(GPIOD, ENABLE);																//Enabling the clock for the bus to which port D is connected to.
	GPIO_Init(&gpioLed);

	gpioButton.pGPIOx = GPIOA; 																		//selecting the port, in this case it is port A where button is connected
	gpioButton.pGPIOx_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	gpioButton.pGPIOx_PinConfig.GPIO_PinMode = GPIO_MODE_IT_RFT;										//Interrupt falling edge trigger when button is released

	gpioButton.pGPIOx_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioButton.pGPIOx_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;									//From schematics its clear already a Pull down resistor is externally connected

	GPIO_PeriClkCtrl(GPIOA, ENABLE);																//Enabling the clock for the bus to which port A is connected to.
	GPIO_Init(&gpioButton);

	//IRQ configuration
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI0, NVIC_IRQ_PRIO_15);
	GPIO_IRQConfig(IRQ_NO_EXTI0, ENABLE);

	while(1);
	return 0;

}

void EXTI0_IRQHandler(void){
	GPIO_IRQHandling(GPIO_PIN_NO_0);//clear pending event
	delay();//200ms
	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);
}

