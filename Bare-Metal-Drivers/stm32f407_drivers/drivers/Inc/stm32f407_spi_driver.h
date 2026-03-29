/*
 * stm32f407_spi_driver.h
 *
 *  Created on: Oct 26, 2025
 *      Author: Abijith Radhakrishnan
 */

#ifndef SRC_STM32F407_SPI_DRIVER_H_
#define SRC_STM32F407_SPI_DRIVER_H_
#include "stm32f407.h"

typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
}SPI_Config_t;

typedef struct
{
	SPI_Regdef_t 	*pSPIx;
	SPI_Config_t 	SPIConfig;
	uint8_t 		*pTxBuffer; /* !< To store the app. Tx buffer address > */
	uint8_t 		*pRxBuffer;	/* !< To store the app. Rx buffer address > */
	uint32_t 		TxLen;		/* !< To store Tx len > */
	uint32_t 		RxLen;		/* !< To store Tx len > */
	uint8_t 		TxState;	/* !< To store Tx state > */
	uint8_t 		RxState;	/* !< To store Rx state > */

}SPI_Handle_t;


/*
 * SPI application states
 */
#define SPI_READY 								0
#define SPI_BUSY_IN_RX 							1
#define SPI_BUSY_IN_TX 							2

/*
 * Possible SPI Application events
 */
#define SPI_EVENT_TX_CMPLT   1
#define SPI_EVENT_RX_CMPLT   2
#define SPI_EVENT_OVR_ERR    3
#define SPI_EVENT_CRC_ERR    4


/*device mode*/
#define SPI_DEVICE_MODE_MASTER					1
#define SPI_DEVICE_MODE_SLAVE					0

/*Bus configuration*/
#define SPI_BUS_CONFIG_FD						1
#define SPI_BUS_CONFIG_HD						2
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY			3

/*Clock speed*/
#define SPI_SCLK_SPEED_DIV2						0
#define SPI_SCLK_SPEED_DIV4						1
#define SPI_SCLK_SPEED_DIV8						2
#define SPI_SCLK_SPEED_DIV16					3
#define SPI_SCLK_SPEED_DIV32					4
#define SPI_SCLK_SPEED_DIV64					5
#define SPI_SCLK_SPEED_DIV128					6
#define SPI_SCLK_SPEED_DIV256					7

/*DFF */
#define SPI_DFF_8BITS							0
#define SPI_DFF_16BITS							1

/*SPI_CPOL */
#define SPI_CPOL_HIGH							1
#define SPI_CPOL_LOW							0

/*SPI_CPHA */
#define SPI_CPHA_HIGH							1
#define SPI_CPHA_LOW							0

/*SPI_SSM */
#define SPI_SSM_EN								1
#define SPI_SSM_DI								0

/*
 * SPI related status flags definitions
 */
#define SPI_TXE_FLAG    						( 1 << SPI_SR_TXE)
#define SPI_RXNE_FLAG   						( 1 << SPI_SR_RXNE)
#define SPI_BUSY_FLAG   						( 1 << SPI_SR_BSY)


/*
 * drivers
 */

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_Regdef_t *pSPIx);
void SPI_PeriClkCtrl(SPI_Regdef_t *pSPIx, uint8_t EnorDi);

/*Data send and receive */

void SPI_SendData(SPI_Regdef_t *pSPIx, uint8_t *pTxBuffer,uint32_t Len);
void SPI_RecieveData(SPI_Regdef_t *pSPIx,uint8_t *pRxBuffer,uint32_t Len);

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandle,uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandle, uint8_t *pRxBuffer, uint32_t Len);

/* IRQ configuration and IRQ handling */

void SPI_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handle_t* pHandle);

/*Other peripheral APIs*/

void SPI_Peripheral_Ctrl(SPI_Regdef_t *pSPIx, uint8_t EnaOrDi);
void SPI_SSIConfig(SPI_Regdef_t *pSPIx, uint8_t EnaOrDi);
void SPI_SSOEConfig(SPI_Regdef_t *pSPIx, uint8_t EnOrDi);
uint8_t SPI_getFlagStatus(SPI_Regdef_t *pSPIx, uint32_t flagName);
void SPI_ClearOVRFlag(SPI_Regdef_t *pSPIx);
void SPI_CloseTransmisson(SPI_Handle_t *pSPIHandle);
void SPI_CloseReception(SPI_Handle_t *pSPIHandle);

/*
 * Application callback
 */
void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle,uint8_t AppEv);

#endif /* SRC_STM32F407_SPI_DRIVER_H_ */
