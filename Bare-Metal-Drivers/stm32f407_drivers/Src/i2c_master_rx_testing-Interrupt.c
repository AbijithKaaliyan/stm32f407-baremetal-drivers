/*
 * i2c_master_rx_testing-Interrupt.c
 *
 *  Created on: Jan 2, 2026
 *      Author: Abijith Radhakrishnan
 */


#include<stdio.h>
#include<string.h>
#include "stm32f407.h"

//extern void initialise_monitor_handles();

//Flag variable
uint8_t rxComplt = RESET;


#define MY_ADDR 0x61;

#define SLAVE_ADDR  0x4A
#define WHO_AM_I    0x01

void delay(void)
{
	for(uint32_t i = 0 ; i < 500000/2 ; i ++);
}

I2C_Handle_t I2C1Handle;

//rcv buffer
uint8_t rcv_buf[32];

/*
 * PB6-> SCL
 * PB9 -> SDA
 */

void I2C1_GPIOInits(void)
{
	GPIO_Handle_t I2CPins;

	I2CPins.pGPIOx = GPIOB;
	I2CPins.pGPIOx_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	I2CPins.pGPIOx_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	I2CPins.pGPIOx_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	I2CPins.pGPIOx_PinConfig.GPIO_PinAltFunMode = 4;
	I2CPins. pGPIOx_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	//scl
	I2CPins.pGPIOx_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&I2CPins);


	//sda
	I2CPins.pGPIOx_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&I2CPins);


}

void I2C1_Inits(void)
{
	I2C1Handle.pI2Cx = I2C1;
	I2C1Handle.I2C_Config.I2C_AckControl = I2C_ACK_ENABLE;
	I2C1Handle.I2C_Config.I2C_DeviceAddress = MY_ADDR;
	I2C1Handle.I2C_Config.I2C_FMDutyCycle = I2C_FM_DUTY_2;
	I2C1Handle.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM;

	I2C_Init(&I2C1Handle);

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


int main(void)
{
	/*
	 * -----------------------------------------------------------------------------
	 * Hardware Setup for I2C Testing (STM32F407 Discovery Board)
	 * -----------------------------------------------------------------------------
	 * Target Device: CS43L22 (Audio DAC)
	 * Why this device?
	 * The LIS302DL (Accelerometer) on this board is hardwired for SPI, not I2C.
	 * The CS43L22 is the only internal peripheral permanently connected to I2C1
	 * (pins PB6 & PB9), making it the perfect candidate for testing I2C drivers.
	 *
	 * Reset Pin Logic (PD4):
	 * The CS43L22 has a hardware RESET pin connected to GPIOD Pin 4.
	 * - State LOW (0): Chip is in Reset (Power down, logic off).
	 * - State HIGH (1): Chip is Active (Listening for I2C commands).
	 *
	 * CRITICAL: The chip will NACK (ignore) all I2C traffic if PD4 is Low.
	 * We must drive PD4 High to wake the chip up before starting I2C.
	 * -----------------------------------------------------------------------------
	 */
	GPIO_Handle_t GPIOAudioRst;
	GPIOAudioRst.pGPIOx = GPIOD;
	GPIOAudioRst.pGPIOx_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GPIOAudioRst.pGPIOx_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOAudioRst.pGPIOx_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOAudioRst.pGPIOx_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOAudioRst.pGPIOx_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_Init(&GPIOAudioRst);
	GPIO_WrtToOutputPin(GPIOD, 4, GPIO_PIN_RESET);
	delay();
	GPIO_WrtToOutputPin(GPIOD, 4, GPIO_PIN_SET);
	delay();

	uint8_t commandcode;

	uint8_t len = 1;

	//initialise_monitor_handles();

	//printf("Application is running\n");

	GPIO_ButtonInit();

	//i2c pin inits
	I2C1_GPIOInits();

	//i2c peripheral configuration
	I2C1_Inits();

	//Enable IRQ config
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_EV, ENABLE);
	I2C_IRQInterruptConfig(IRQ_NO_I2C1_ER, ENABLE);

	//enable the i2c peripheral
	I2C_PeripheralControl(I2C1,ENABLE);

	//ack bit is made 1 after PE=1
	I2C_ManageAcking(I2C1,I2C_ACK_ENABLE);

	while(1)
	{
		//wait till button is pressed
		while( ! GPIO_ReadFrmInptPin(GPIOA,GPIO_PIN_NO_0) );

		//to avoid button de-bouncing related issues 200ms of delay
		delay();

		commandcode = WHO_AM_I;

		while(I2C_MasterSendDataIT(&I2C1Handle,&commandcode,1,SLAVE_ADDR,I2C_ENABLE_SR)!= I2C_READY);

		while(I2C_MasterReceiveDataIT(&I2C1Handle,rcv_buf,1,SLAVE_ADDR,I2C_DISABLE_SR)!= I2C_READY);

		//commandcode = 0x52;
		//I2C_MasterSendData(&I2C1Handle,&commandcode,1,SLAVE_ADDR,I2C_ENABLE_SR);


		//I2C_MasterReceiveData(&I2C1Handle,rcv_buf,len,SLAVE_ADDR,I2C_DISABLE_SR);

		rcv_buf[len+1] = '\0';

		//printf("Data : %s",rcv_buf);

	}

}

void I2C1_EV_IRQHandler (void)
{
	I2C_EV_IRQHandling(&I2C1Handle);
}


void I2C1_ER_IRQHandler (void)
{
	I2C_ER_IRQHandling(&I2C1Handle);
}

void I2C_ApplicationEventCallback(I2C_Handle_t *pI2CHandle,uint8_t AppEv)
{
     if(AppEv == I2C_EV_TX_CMPLT)
     {
    	 //printf("Tx is completed\n");
     }else if (AppEv == I2C_EV_RX_CMPLT)
     {
    	 //printf("Rx is completed\n");
    	 rxComplt = SET;
     }else if (AppEv == I2C_ERROR_AF)
     {
    	 //printf("Error : Ack failure\n");
    	 //in master ack failure happens when slave fails to send ack for the byte
    	 //sent from the master.
    	 I2C_CloseSendData(pI2CHandle);

    	 //generate the stop condition to release the bus
    	 I2C_GenerateStopCondition(I2C1);

    	 //Hang in infinite loop
    	 while(1);
     }
}
