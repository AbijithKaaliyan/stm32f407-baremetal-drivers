/*
 * 002LedButton.c
 *
 *  Created on: Oct 22, 2025
 *      Author: Abijith Radhakrishnan
 */

#include "stm32f407.h"
#define HIGH 1
#define BTN_PRESSED HIGH

void delay(void){

	for(volatile uint32_t i = 0; i< 500000/2; i++);
}


int main (void) {

	GPIO_Handle_t gpioLed,gpioButton;
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
	gpioButton.pGPIOx_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	gpioButton.pGPIOx_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioButton.pGPIOx_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;									//From schematics its clear already a Pull down resistor is externally connected

	GPIO_PeriClkCtrl(GPIOA, ENABLE);																//Enabling the clock for the bus to which port A is connected to.
	GPIO_Init(&gpioButton);

	while(1){
		if(GPIO_ReadFrmInptPin(GPIOA,GPIO_PIN_NO_0) == BTN_PRESSED){
			delay();
			GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12);											// LED toggled with a delay
		}

	}
	return 0;

}

