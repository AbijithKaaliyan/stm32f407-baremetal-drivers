/*
 * spi_cmd_handling.c
 *
 *  Created on: Nov 14, 2025
 *      Author: Abijith Radhakrishnan
 */

#include "stm32f407.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>

//extern void initialise_monitor_handles();

//command codes
#define COMMAND_LED_CTRL      		0x50
#define COMMAND_SENSOR_READ      	0x51
#define COMMAND_LED_READ      		0x52
#define COMMAND_PRINT      			0x53
#define COMMAND_ID_READ      		0x54

#define LED_ON     1
#define LED_OFF    0

//arduino analog pins
#define ANALOG_PIN0 	0
#define ANALOG_PIN1 	1
#define ANALOG_PIN2 	2
#define ANALOG_PIN3 	3
#define ANALOG_PIN4 	4

//arduino led

#define LED_PIN  9

#define HIGH 1
#define BTN_PRESSED HIGH

void delay(void){

	for(volatile uint32_t i = 0; i< 500000/2; i++);
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

	SPIpins.pGPIOx_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_14;//MISO		//Since there is no receiving signal here just disabled for now
	GPIO_Init(&SPIpins);

	SPIpins.pGPIOx_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;//NSS
	GPIO_Init(&SPIpins);


}


void SPI2_Init(void){

	SPI_Handle_t SPI2Handle;
	SPI2Handle.pSPIx = SPI2;
	SPI2Handle.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2Handle.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2Handle.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;   		//generate SCLK of 2MHZ since 16/8
	SPI2Handle.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2Handle.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2Handle.SPIConfig.SPI_SSM = SPI_SSM_DI; 							//Hardware slave management enabled for NSS Pin
	SPI_Init(&SPI2Handle);
}


uint8_t SPI_VerifyResponse(uint8_t ackbyte)
{

	if(ackbyte == (uint8_t)0xF5)
	{
		//ack
		return 1;
	}

	return 0;
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

	uint8_t dummyWrite = 0xff;
	uint8_t dummyRead;

	SPI2_GPIOInit();

	//Initialize SPI2 peripheral parameters
	SPI2_Init();

	//Make SSOE 1, so that Hardware NSS signal can toggle with SPE
	SPI_SSOEConfig(SPI2, ENABLE);


	while(1)
	{
		//wait till button is pressed
		while( ! GPIO_ReadFrmInptPin(GPIOA,GPIO_PIN_NO_0) );

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		//enable the SPI2 peripheral
		SPI_Peripheral_Ctrl(SPI2,ENABLE);

	    //1. CMD_LED_CTRL  	<pin no(1)>     <value(1)>

		uint8_t commandcode = COMMAND_LED_CTRL;
		uint8_t ackbyte;
		uint8_t args[2];

		//send command
		SPI_SendData(SPI2,&commandcode,1);

		//do dummy read to clear off the RXNE
		SPI_RecieveData(SPI2,&dummyRead,1);


		//Send some dummy bits (1 byte) fetch the response from the slave
		SPI_SendData(SPI2,&dummyWrite,1);

		//read the ack byte received
		SPI_RecieveData(SPI2,&ackbyte,1);

		if( SPI_VerifyResponse(ackbyte))
		{
			args[0] = LED_PIN;
			args[1] = LED_ON;

			//send arguments
			SPI_SendData(SPI2,args,2);
			// dummy read
			SPI_RecieveData(SPI2,args,2);
			//printf("COMMAND_LED_CTRL Executed\n");
		}
		//end of COMMAND_LED_CTRL




		//2. CMD_SENOSR_READ   <analog pin number(1) >

		//wait till button is pressed
		while( ! GPIO_ReadFrmInptPin(GPIOA,GPIO_PIN_NO_0) );

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		commandcode = COMMAND_SENSOR_READ;

		//send command
		SPI_SendData(SPI2,&commandcode,1);

		//do dummy read to clear off the RXNE
		SPI_RecieveData(SPI2,&dummyRead,1);


		//Send some dummy byte to fetch the response from the slave
		SPI_SendData(SPI2,&dummyWrite,1);

		//read the ack byte received
		SPI_RecieveData(SPI2,&ackbyte,1);

		if( SPI_VerifyResponse(ackbyte))
		{
			args[0] = ANALOG_PIN0;

			//send arguments
			SPI_SendData(SPI2,args,1); //sending one byte of

			//do dummy read to clear off the RXNE
			SPI_RecieveData(SPI2,&dummyRead,1);

			//insert some delay so that slave can ready with the data
			delay();

			//Send some dummy bits (1 byte) fetch the response from the slave
			SPI_SendData(SPI2,&dummyWrite,1);

			uint8_t analog_read;
			SPI_RecieveData(SPI2,&analog_read,1);
			//printf("COMMAND_SENSOR_READ %d\n",analog_read);
		}

		//3.  CMD_LED_READ 	 <pin no(1) >

		//wait till button is pressed
		while( ! GPIO_ReadFrmInptPin(GPIOA,GPIO_PIN_NO_0) );

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		commandcode = COMMAND_LED_READ;

		//send command
		SPI_SendData(SPI2,&commandcode,1);

		//do dummy read to clear off the RXNE
		SPI_RecieveData(SPI2,&dummyRead,1);

		//Send some dummy byte to fetch the response from the slave
		SPI_SendData(SPI2,&dummyWrite,1);

		//read the ack byte received
		SPI_RecieveData(SPI2,&ackbyte,1);

		if( SPI_VerifyResponse(ackbyte))
		{
			args[0] = LED_PIN;

			//send arguments
			SPI_SendData(SPI2,args,1); //sending one byte of

			//do dummy read to clear off the RXNE
			SPI_RecieveData(SPI2,&dummyRead,1);

			//insert some delay so that slave can ready with the data
			delay();

			//Send some dummy bits (1 byte) fetch the response from the slave
			SPI_SendData(SPI2,&dummyWrite,1);

			uint8_t led_status;
			SPI_RecieveData(SPI2,&led_status,1);
			//printf("COMMAND_READ_LED %d\n",led_status);

		}

		//4. CMD_PRINT 		<len(2)>  <message(len) >

		//wait till button is pressed
		while( ! GPIO_ReadFrmInptPin(GPIOA,GPIO_PIN_NO_0) );

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		commandcode = COMMAND_PRINT;

		//send command
		SPI_SendData(SPI2,&commandcode,1);

		//do dummy read to clear off the RXNE
		SPI_RecieveData(SPI2,&dummyRead,1);

		//Send some dummy byte to fetch the response from the slave
		SPI_SendData(SPI2,&dummyWrite,1);

		//read the ack byte received
		SPI_RecieveData(SPI2,&ackbyte,1);

		uint8_t message[] = "Hello ! How are you ??";
		if( SPI_VerifyResponse(ackbyte))
		{
			args[0] = strlen((char*)message);

			//send arguments
			SPI_SendData(SPI2,args,1); //sending length

			//do dummy read to clear off the RXNE
			SPI_RecieveData(SPI2,&dummyRead,1);

			delay();

			//send message
			for(int i = 0 ; i < args[0] ; i++){
				SPI_SendData(SPI2,&message[i],1);
				SPI_RecieveData(SPI2,&dummyRead,1);
			}

			//printf("COMMAND_PRINT Executed \n");

		}

		//5. CMD_ID_READ
		//wait till button is pressed
		while( ! GPIO_ReadFrmInptPin(GPIOA,GPIO_PIN_NO_0) );

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		commandcode = COMMAND_ID_READ;

		//send command
		SPI_SendData(SPI2,&commandcode,1);

		//do dummy read to clear off the RXNE
		SPI_RecieveData(SPI2,&dummyRead,1);

		//Send some dummy byte to fetch the response from the slave
		SPI_SendData(SPI2,&dummyWrite,1);

		//read the ack byte received
		SPI_RecieveData(SPI2,&ackbyte,1);

		uint8_t id[11];
		uint32_t i=0;
		if( SPI_VerifyResponse(ackbyte))
		{
			//read 10 bytes id from the slave
			for(  i = 0 ; i < 10 ; i++)
			{
				//send dummy byte to fetch data from slave
				SPI_SendData(SPI2,&dummyWrite,1);
				SPI_RecieveData(SPI2,&id[i],1);
			}

			id[10] = '\0';

			//printf("COMMAND_ID : %s \n",id);

		}

		//lets confirm SPI is not busy
		while( SPI_getFlagStatus(SPI2,SPI_BUSY_FLAG) );

		//Disable the SPI2 peripheral
		SPI_Peripheral_Ctrl(SPI2,DISABLE);

		//printf("SPI Communication Closed\n");
	}

	return 0;
}


