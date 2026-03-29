/*
 * SPI_txOnlyToArduino.c
 *
 *  Created on: Nov 9, 2025
 *      Author: Abijith Radhakrishnan
 */


#include "stm32f407.h"
#include <string.h>

#define HIGH 1
#define BTN_PRESSED HIGH

void delay(void){

	for(volatile uint32_t i = 0; i< 500000; i++);
}

//Here I am using PB15 as SPI2_MOSI, PB14 as SPI2_MISO, PB13 as SPI2_SCLK and PB12 as SPI2_NSS (as referred to the alternate functionality of pins in the datasheet of the board )
//Alternate functionality mode AF5


void SPI2_GPIOInit(void){

	GPIO_Handle_t SPIpins;
	SPIpins.pGPIOx = GPIOB;
	SPIpins.pGPIOx_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	SPIpins.pGPIOx_PinConfig.GPIO_PinAltFunMode = 5;
	SPIpins.pGPIOx_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	SPIpins.pGPIOx_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	SPIpins.pGPIOx_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	SPIpins.pGPIOx_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;//MOSI
	GPIO_Init(&SPIpins);

	SPIpins.pGPIOx_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_13;//SCLK
	GPIO_Init(&SPIpins);

//	SPIpins.pGPIOx_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;//MISO		//Since there is no receiving signal here just disabled for now
//	GPIO_Init(&SPIpins);

	SPIpins.pGPIOx_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;//NSS
	GPIO_Init(&SPIpins);


}


void SPI2_Init(void){

	SPI_Handle_t SPI2Handle;
	SPI2Handle.pSPIx = SPI2;
	SPI2Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV32;   		//generate SCLK of 2MHZ since 16/8
	SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_DI; 							//Hardware slave management enabled for NSS Pin
	SPI_Init(&SPI2Handle);
}


int main(void)
{
	GPIO_Handle_t gpioButton;

	gpioButton.pGPIOx = GPIOA; 																		//selecting the port, in this case it is port A where button is connected
	gpioButton.pGPIOx_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	gpioButton.pGPIOx_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	gpioButton.pGPIOx_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	gpioButton.pGPIOx_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;									//From schematics its clear already a Pull down resistor is externally connected

	GPIO_Init(&gpioButton);

	char user_data[] = "I am Abijith";
	//Initializing corresponding GPIO pins to behave as SPI functionality pins

	SPI2_GPIOInit();

	//Initialize SPI2 peripheral parameters
	SPI2_Init();

	//Make SSOE 1, so that Hardware NSS signal can toggle with SPE
	SPI_SSOEConfig(SPI2, ENABLE);


	while(1){
		if(GPIO_ReadFrmInptPin(GPIOA,GPIO_PIN_NO_0) == BTN_PRESSED){
			delay();

			//Enable SPI2 peripheral

			SPI_Peripheral_Ctrl(SPI2, ENABLE);

			//send length or number of byte information to the slave
			uint8_t dataLen = strlen(user_data);
			SPI_SendData(SPI2, &dataLen, 1);

			//Send data

			SPI_SendData(SPI2, (uint8_t*)user_data, strlen(user_data));

			//confirming SPI communication is not busy
			while(SPI_getFlagStatus(SPI2,SPI_BUSY_FLAG));

			SPI_Peripheral_Ctrl(SPI2,DISABLE);
		}

	}

	return 0;
}

