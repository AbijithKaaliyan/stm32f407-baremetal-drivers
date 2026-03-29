/*
 * stm32f407.h
 *
 *  Created on: Oct 19, 2025
 *      Author: Abijith_Radhakrishnan
 */

#ifndef INC_STM32F407_H_
#define INC_STM32F407_H_
#include <stdint.h>
#include <stddef.h>
#define __vo volatile
#define __weak __attribute__((weak))

/*
 * ARM processor NVIC specifc register location
 */
#define NVIC_ISER0 												((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1 												((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2 												((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3 												((__vo uint32_t*)0xE000E10C)

#define NVIC_ICER0 												((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1 												((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2 												((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3 												((__vo uint32_t*)0xE000E18C)

/*
 * ARM processor NVIC INterrupt priority register location
 */

#define NVIC_PR_BASE_ADDR										((__vo uint32_t*)0xE000E400)

#define NO_PR_BITS_IMPLEMENTED									4								/*Incase of this MCU only upper 4 bits of 8 bit Interrupt prio register is considered for implementation*/


/*
 * 	Base addresses of Flash and SRAM memories (here for now just using SRAM1 as main SRAM)
 */

#define FLASH_BASEADDR											0x08000000U 					/*Base address of the FLASH memory*/
#define SRAM1_BASEADDR											0x20000000U						/*Base address of the SRAM1 memory*/
#define SRAM2_BASEADDR											SRAM1_BASEADDR + (1C000)		/*Base address of the SRAM2 memory (SRAM1 + size of SRAM1)*/
#define SRAM 													SRAM1_BASEADDR					/*Selecting SRAM1 as default SRAM*/


#define PERIPH_BASEADDR											0x40000000U						/*Base address of peripheral */
#define APB1PERIPH_BASEADDR										PERIPH_BASEADDR					/*Base address of APB1 */
#define APB2PERIPH_BASEADDR										0x40010000U						/*Base address of APB2 */
#define AHB1PERIPH_BASEADDR										0x40020000U						/*Base address of AHB1 */
#define AHB2PERIPH_BASEADDR										0x50000000U						/*Base address of AHB2 */

/*
 * 	Base addresses of peripherals connected to AHB1 bus
 */

#define GPIOA_BASEADDR											(AHB1PERIPH_BASEADDR + 0x0000) 	/*Base address of GPIOA, offset is 0x0000 from AHB1*/
#define GPIOB_BASEADDR											(AHB1PERIPH_BASEADDR + 0x0400) 	/*Base address of GPIOB, offset is 0x0400 from AHB1*/
#define GPIOC_BASEADDR											(AHB1PERIPH_BASEADDR + 0x0800) 	/*Base address of GPIOC, offset is 0x0800 from AHB1*/
#define GPIOD_BASEADDR											(AHB1PERIPH_BASEADDR + 0x0C00U) 	/*Base address of GPIOD, offset is 0x0C00 from AHB1*/
#define GPIOE_BASEADDR											(AHB1PERIPH_BASEADDR + 0x1000) 	/*Base address of GPIOE, offset is 0x1000 from AHB1*/
#define GPIOF_BASEADDR											(AHB1PERIPH_BASEADDR + 0x1400) 	/*Base address of GPIOF, offset is 0x1400 from AHB1*/
#define GPIOG_BASEADDR											(AHB1PERIPH_BASEADDR + 0x1800) 	/*Base address of GPIOG, offset is 0x1800 from AHB1*/
#define GPIOH_BASEADDR											(AHB1PERIPH_BASEADDR + 0x1C00) 	/*Base address of GPIOH, offset is 0x1C00 from AHB1*/
#define GPIOI_BASEADDR											(AHB1PERIPH_BASEADDR + 0x2000) 	/*Base address of GPIOI, offset is 0x2000 from AHB1*/
#define RCC_BASEADDR											(AHB1PERIPH_BASEADDR + 0x3800)	/*Base address of RCC, offset is 0x3800 from AHB1*/

/*
 * 	Base addresses of peripherals connected to APB1 bus
 */

#define I2C1_BASEADDR											(APB1PERIPH_BASEADDR + 0x5400) 	/*Base address of I2C1, offset is 0x5400 from APB1*/
#define I2C2_BASEADDR											(APB1PERIPH_BASEADDR + 0x5800) 	/*Base address of I2C2, offset is 0x5800 from APB1*/
#define I2C3_BASEADDR											(APB1PERIPH_BASEADDR + 0x5C00) 	/*Base address of I2C3, offset is 0x5C00 from APB1*/
#define SPI2_BASEADDR											(APB1PERIPH_BASEADDR + 0x3800) 	/*Base address of SPI2, offset is 0x3800 from APB1*/
#define SPI3_BASEADDR											(APB1PERIPH_BASEADDR + 0x3C00) 	/*Base address of SPI3, offset is 0x3C00 from APB1*/
#define USART2_BASEADDR											(APB1PERIPH_BASEADDR + 0x4400) 	/*Base address of USART2, offset is 0x4400 from APB1*/
#define USART3_BASEADDR											(APB1PERIPH_BASEADDR + 0x4800) 	/*Base address of USART3, offset is 0x4800 from APB1*/
#define UART4_BASEADDR											(APB1PERIPH_BASEADDR + 0x4C00) 	/*Base address of UART4, offset is 0x4C00 from APB1*/
#define UART5_BASEADDR											(APB1PERIPH_BASEADDR + 0x5000) 	/*Base address of UART5, offset is 0x5000 from APB1*/

/*
 * 	Base addresses of peripherals connected to APB2 bus
 */

#define EXTI_BASEADDR											(APB2PERIPH_BASEADDR + 0x3C00) 	/*Base address of EXTI, offset is 0x3C00 from APB2*/
#define SPI1_BASEADDR											(APB2PERIPH_BASEADDR + 0x3000) 	/*Base address of SPI1, offset is 0x3000 from APB2*/
#define USART1_BASEADDR											(APB2PERIPH_BASEADDR + 0x1000) 	/*Base address of USART1, offset is 0x1000 from APB2*/
#define USART6_BASEADDR											(APB2PERIPH_BASEADDR + 0x1400) 	/*Base address of USART6, offset is 0x1400 from APB2*/
#define SYSCFG_BASEADDR											(APB2PERIPH_BASEADDR + 0x3800) 	/*Base address of SYSCFG, offset is 0x3800 from APB2*/


/************************************************************Peripheral registers definition structures************************************************************************************/

typedef struct
{

	__vo uint32_t  MODER;																			/*GPIO port mode register, Address offset: 0x00*/
	__vo uint32_t  OTYPER;																			/*GPIO port output type register, Address offset: 0x04*/
	__vo uint32_t  OSPEEDR;																			/*GPIO port output speed register, Address offset: 0x08*/
	__vo uint32_t  PUPDR;																			/*GPIO port pull-up/pull-down register, Address offset: 0x0C*/
	__vo uint32_t  IDR;																				/*GPIO port input data register , Address offset: 0x10*/
	__vo uint32_t  ODR;																				/*GPIO port output data register , Address offset: 0x14*/
	__vo uint32_t  BSRR;																			/*GPIO port bit set/reset register, Address offset: 0x18*/
	__vo uint32_t  LCKR;																			/*GPIO port configuration lock register, Address offset: 0x1C*/
	__vo uint32_t  AFR[2];																			/*AFR[0]:GPIO alternate function low register,AFR[1]: GPIO alternate function high register , Address offset: 0x20 and 0x24*/

} GPIO_Regdef_t;


typedef struct
{

	__vo uint32_t  RCC_CR;																			/*Address offset: 0x00*/
	__vo uint32_t  PLLCFGR;																			/*Address offset: 0x04*/
	__vo uint32_t  CFGR;																			/*Address offset: 0x08*/
	__vo uint32_t  CIR;																				/*Address offset: 0x0C*/
	__vo uint32_t  AHB1RSTR;																		/*Address offset: 0x10*/
	__vo uint32_t  AHB2RSTR;																		/*Address offset: 0x14*/
	__vo uint32_t  AHB3RSTR;																		/*Address offset: 0x18*/
	uint32_t  		RSERVED0;																		/*Address offset: 0x1C*/
	__vo uint32_t  APB1RSTR;																		/*Address offset: 0x20*/
	__vo uint32_t  APB2RSTR;																		/*Address offset: 0x24*/
	uint32_t  		RESERVED1[2];																	/*Address offset: 0x28,0x2C*/
	__vo uint32_t  AHB1ENR;																			/*Address offset: 0x30*/
	__vo uint32_t  AHB2ENR;																			/*Address offset: 0x34*/
	__vo uint32_t  AHB3ENR;																			/*Address offset: 0x38*/
	uint32_t  		RESERVED2;																		/*Address offset: 0x3C*/
	__vo uint32_t  APB1ENR;																			/*Address offset: 0x40*/
	__vo uint32_t  APB2ENR;																			/*Address offset: 0x44*/
	uint32_t  		RESERVED3[2];																	/*Address offset: 0x48,0x4C*/
	__vo uint32_t  AHB1LPENR;																		/*Address offset: 0x50*/
	__vo uint32_t  AHB2LPENR;																		/*Address offset: 0x54*/
	__vo uint32_t  AHB3LPENR;																		/*Address offset: 0x58*/
	uint32_t  		RESERVED4;																		/*Address offset: 0x5C*/
	__vo uint32_t  APB1LPENR;																		/*Address offset: 0x60*/
	__vo uint32_t  APB2LPENR;																		/*Address offset: 0x64*/
	uint32_t  		RESERVED5[2];																	/*Address offset: 0x68,0x6C*/
	__vo uint32_t  BDCR;																			/*Address offset: 0x70*/
	__vo uint32_t  CSR;																				/*Address offset: 0x74*/
	uint32_t  RESERVED6[2];																			/*Address offset: 0x78,ox7C*/
	__vo uint32_t  SSCGR;																			/*Address offset: 0x80*/
	__vo uint32_t  PLLI2SCFGR;																		/*Address offset: 0x84*/



}RCC_Regdef_t;


typedef struct
{

	__vo uint32_t  IMR;																				/*Address offset: 0x00*/
	__vo uint32_t  EMR;																				/*Address offset: 0x04*/
	__vo uint32_t  RTSR;																			/*Address offset: 0x08*/
	__vo uint32_t  FTSR;																			/*Address offset: 0x0C*/
	__vo uint32_t  SWIER;																			/*Address offset: 0x10*/
	__vo uint32_t  PR;																				/*Address offset: 0x14*/

}EXTI_Regdef_t;

typedef struct
{

	__vo uint32_t  MEMRMP;																			/*GPIO port mode register, Address offset: 0x00*/
	__vo uint32_t  PMC;																				/*GPIO port output type register, Address offset: 0x04*/
	__vo uint32_t  EXTICR[4];																		/*GPIO port output speed register, Address offset: 0x08 - 0x14*/
	uint32_t  RESERVED[2];																			/*Address offset: 0x18 - 1C*/
	__vo uint32_t  CMPCR;																			/*GPIO port bit set/reset register, Address offset: 0x20*/

} SYSCFG_Regdef_t;

typedef struct
{

	__vo uint32_t  CR1;																				/*Address offset: 0x00*/
	__vo uint32_t  CR2;																				/*Address offset: 0x04*/
	__vo uint32_t  SR;																				/*Address offset: 0x08*/
	__vo uint32_t  DR;																				/*Address offset: 0x0C*/
	__vo uint32_t  CRCPR;																			/*Address offset: 0x10*/
	__vo uint32_t  RXCRCR;																			/*Address offset: 0x14*/
	__vo uint32_t  TXCRCR;																			/*Address offset: 0x18*/
	__vo uint32_t  I2SCFGR;																			/*Address offset: 0x1C*/
	__vo uint32_t  I2SPR;																			/*Address offset: 0x20*/

}SPI_Regdef_t;

/*
 * peripheral register definition structure for I2C
 */
typedef struct
{
  __vo uint32_t CR1;        /*     																	Address offset: 0x00 */
  __vo uint32_t CR2;        /*     																	Address offset: 0x04 */
  __vo uint32_t OAR1;       /*     																	Address offset: 0x08 */
  __vo uint32_t OAR2;       /*     																	Address offset: 0x0C */
  __vo uint32_t DR;         /*    																	Address offset: 0x10 */
  __vo uint32_t SR1;        /*     																	Address offset: 0x14 */
  __vo uint32_t SR2;        /*    																	Address offset: 0x18 */
  __vo uint32_t CCR;        /*     																	Address offset: 0x1C */
  __vo uint32_t TRISE;      /*     																	Address offset: 0x20 */
  __vo uint32_t FLTR;       /*     																	Address offset: 0x24 */
}I2C_RegDef_t;

/*
 * peripheral register definition structure for USART
 */
typedef struct
{
	__vo uint32_t SR;         /*!Status register,     												Address offset: 0x00 */
	__vo uint32_t DR;         /*!Data register,     												Address offset: 0x04 */
	__vo uint32_t BRR;        /*!Baud Rate Register,     											Address offset: 0x08 */
	__vo uint32_t CR1;        /*!Control register 1,     											Address offset: 0x0C */
	__vo uint32_t CR2;        /*!Control register 2,     											Address offset: 0x10 */
	__vo uint32_t CR3;        /*!Control register 3,     											Address offset: 0x14 */
	__vo uint32_t GTPR;       /*!Guard Time and Prescaler Register,     							Address offset: 0x18 */
} USART_RegDef_t;


/*
 * Peripheral definitions (Peripheral base addresses typecasted to xxx_RegDef_t)
 */

#define GPIOA													((GPIO_Regdef_t*)GPIOA_BASEADDR)
#define GPIOB													((GPIO_Regdef_t*)GPIOB_BASEADDR)
#define GPIOC													((GPIO_Regdef_t*)GPIOC_BASEADDR)
#define GPIOD													((GPIO_Regdef_t*)GPIOD_BASEADDR)
#define GPIOE													((GPIO_Regdef_t*)GPIOE_BASEADDR)
#define GPIOF													((GPIO_Regdef_t*)GPIOF_BASEADDR)
#define GPIOG													((GPIO_Regdef_t*)GPIOG_BASEADDR)
#define GPIOH													((GPIO_Regdef_t*)GPIOH_BASEADDR)
#define GPIOI													((GPIO_Regdef_t*)GPIOI_BASEADDR)

#define RCC														((RCC_Regdef_t*)RCC_BASEADDR)

#define EXTI													((EXTI_Regdef_t*)EXTI_BASEADDR)

#define SYSCFG													((SYSCFG_Regdef_t*)SYSCFG_BASEADDR)

#define SPI1													((SPI_Regdef_t*)SPI1_BASEADDR)
#define SPI2													((SPI_Regdef_t*)SPI2_BASEADDR)
#define SPI3													((SPI_Regdef_t*)SPI3_BASEADDR)

#define I2C1  													((I2C_RegDef_t*)I2C1_BASEADDR)
#define I2C2  													((I2C_RegDef_t*)I2C2_BASEADDR)
#define I2C3  													((I2C_RegDef_t*)I2C3_BASEADDR)

#define USART1  												((USART_RegDef_t*)USART1_BASEADDR)
#define USART2  												((USART_RegDef_t*)USART2_BASEADDR)
#define USART3  												((USART_RegDef_t*)USART3_BASEADDR)
#define UART4  													((USART_RegDef_t*)UART4_BASEADDR)
#define UART5  													((USART_RegDef_t*)UART5_BASEADDR)
#define USART6  												((USART_RegDef_t*)USART6_BASEADDR)



/*
 * Clock enable macros for GPIOx peripherals
 */
#define GPIOA_PCLK_EN()											(RCC ->AHB1ENR |= (1<<0))
#define GPIOB_PCLK_EN()											(RCC ->AHB1ENR |= (1<<1))
#define GPIOC_PCLK_EN()											(RCC ->AHB1ENR |= (1<<2))
#define GPIOD_PCLK_EN()											(RCC ->AHB1ENR |= (1<<3))
#define GPIOE_PCLK_EN()											(RCC ->AHB1ENR |= (1<<4))
#define GPIOF_PCLK_EN()											(RCC ->AHB1ENR |= (1<<5))
#define GPIOG_PCLK_EN()											(RCC ->AHB1ENR |= (1<<6))
#define GPIOH_PCLK_EN()											(RCC ->AHB1ENR |= (1<<7))
#define GPIOI_PCLK_EN()											(RCC ->AHB1ENR |= (1<<8))

/*
 * Clock enable macros for I2Cx peripherals
 */
#define I2C1_PCLK_EN()											(RCC ->APB1ENR |= (1<<21))
#define I2C2_PCLK_EN()											(RCC ->APB1ENR |= (1<<22))
#define I2C3_PCLK_EN()											(RCC ->APB1ENR |= (1<<23))

/*
 * Clock enable macros for UARTx peripherals
 */
#define UART4_PCLK_EN()											(RCC ->APB1ENR |= (1<<19))
#define UART5_PCLK_EN()											(RCC ->APB1ENR |= (1<<20))

/*
 * Clock enable macros for USARTx peripherals
 */
#define USART1_PCLK_EN()										(RCC ->APB2ENR |= (1<<4))
#define USART2_PCLK_EN()										(RCC ->APB1ENR |= (1<<17))
#define USART3_PCLK_EN()										(RCC ->APB1ENR |= (1<<18))
#define USART6_PCLK_EN()										(RCC ->APB2ENR |= (1<<5))

/*
 * Clock enable macros for SPIx peripherals
 */
#define SPI1_PCLK_EN()											(RCC ->APB2ENR |= (1<<12))
#define SPI2_PCLK_EN()											(RCC ->APB1ENR |= (1<<14))
#define SPI3_PCLK_EN()											(RCC ->APB1ENR |= (1<<15))

/*
 * Clock enable macros for SYSCFG peripherals
 */
#define SYSCFG_PCLK_EN()										(RCC ->APB2ENR |= (1<<14))

/*
 * Clock disable macros for GPIOx peripherals
 */
#define GPIOA_PCLK_DI()											(RCC ->AHB1ENR &= ~(1<<0))
#define GPIOB_PCLK_DI()											(RCC ->AHB1ENR &= ~(1<<1))
#define GPIOC_PCLK_DI()											(RCC ->AHB1ENR &= ~(1<<2))
#define GPIOD_PCLK_DI()											(RCC ->AHB1ENR &= ~(1<<3))
#define GPIOE_PCLK_DI()											(RCC ->AHB1ENR &= ~(1<<4))
#define GPIOF_PCLK_DI()											(RCC ->AHB1ENR &= ~(1<<5))
#define GPIOG_PCLK_DI()											(RCC ->AHB1ENR &= ~(1<<6))
#define GPIOH_PCLK_DI()											(RCC ->AHB1ENR &= ~(1<<7))
#define GPIOI_PCLK_DI()											(RCC ->AHB1ENR &= ~(1<<8))

/*
 * Clock disable macros for I2Cx peripherals
 */
#define I2C1_PCLK_DI()											(RCC ->APB1ENR &= ~(1<<21))
#define I2C2_PCLK_DI()											(RCC ->APB1ENR &= ~(1<<22))
#define I2C3_PCLK_DI()											(RCC ->APB1ENR &= ~(1<<23))

/*
 * Clock disable macros for UARTx peripherals
 */
#define UART4_PCLK_DI()											(RCC ->APB1ENR &= ~(1<<19))
#define UART5_PCLK_DI()											(RCC ->APB1ENR &= ~(1<<20))

/*
 * Clock disable macros for USARTx peripherals
 */
#define USART1_PCLK_DI()										(RCC ->APB2ENR &= ~(1<<4))
#define USART2_PCLK_DI()										(RCC ->APB1ENR &= ~(1<<17))
#define USART3_PCLK_DI()										(RCC ->APB1ENR &= ~(1<<18))
#define USART6_PCLK_DI()										(RCC ->APB2ENR &= ~(1<<5))

/*
 * Clock disable macros for SPIx peripherals
 */
#define SPI1_PCLK_DI()											(RCC ->APB2ENR &= ~(1<<12))
#define SPI2_PCLK_DI()											(RCC ->APB1ENR &= ~(1<<14))
#define SPI3_PCLK_DI()											(RCC ->APB1ENR &= ~(1<<15))

/*
 * Clock disable macros for SYSCFG peripherals
 */
#define SYSCFG_PCLK_DI()										(RCC ->APB2ENR &= ~(1<<14))

/*
 * Macros to reset GPIOx peripherals
 */

#define GPIOA_REG_RESET()										do{(RCC ->AHB1RSTR |= (1<<0));	(RCC ->AHB1RSTR &= ~(1<<0)); }while (0)
#define GPIOB_REG_RESET()										do{(RCC ->AHB1RSTR |= (1<<1));	(RCC ->AHB1RSTR &= ~(1<<1)); }while (0)
#define GPIOC_REG_RESET()										do{(RCC ->AHB1RSTR |= (1<<2));	(RCC ->AHB1RSTR &= ~(1<<2)); }while (0)
#define GPIOD_REG_RESET()										do{(RCC ->AHB1RSTR |= (1<<3));	(RCC ->AHB1RSTR &= ~(1<<3)); }while (0)
#define GPIOE_REG_RESET()										do{(RCC ->AHB1RSTR |= (1<<4));	(RCC ->AHB1RSTR &= ~(1<<4)); }while (0)
#define GPIOF_REG_RESET()										do{(RCC ->AHB1RSTR |= (1<<5));	(RCC ->AHB1RSTR &= ~(1<<5)); }while (0)
#define GPIOG_REG_RESET()										do{(RCC ->AHB1RSTR |= (1<<6));	(RCC ->AHB1RSTR &= ~(1<<6)); }while (0)
#define GPIOH_REG_RESET()										do{(RCC ->AHB1RSTR |= (1<<7));	(RCC ->AHB1RSTR &= ~(1<<7)); }while (0)
#define GPIOI_REG_RESET()										do{(RCC ->AHB1RSTR |= (1<<8));	(RCC ->AHB1RSTR &= ~(1<<8)); }while (0)

#define GPIO_BASEADDR_TO_CODE(x)								((x==GPIOA) ? 0 :\
																(x==GPIOB) ? 1 :\
																(x==GPIOC) ? 2 :\
																(x==GPIOD) ? 3 :\
																(x==GPIOE) ? 4 :\
																(x==GPIOF) ? 5 :\
																(x==GPIOG) ? 6 :\
																(x==GPIOH) ? 7 :\
																(x==GPIOI) ? 8 :0)

#define IRQ_NO_EXTI0											6
#define IRQ_NO_EXTI1											7
#define IRQ_NO_EXTI2											8
#define IRQ_NO_EXTI3											9
#define IRQ_NO_EXTI4											10
#define IRQ_NO_EXTI9_5											23
#define IRQ_NO_EXTI5_10											40
#define IRQ_NO_SPI1												35
#define IRQ_NO_SPI2         									36
#define IRQ_NO_SPI3         									51
#define IRQ_NO_I2C1_EV     										31
#define IRQ_NO_I2C1_ER     										32
#define IRQ_NO_USART1	    									37
#define IRQ_NO_USART2	    									38
#define IRQ_NO_USART3	    									39
#define IRQ_NO_UART4	    									52
#define IRQ_NO_UART5	    									53
#define IRQ_NO_USART6	    									71

#define NVIC_IRQ_PRIO_0											0
#define NVIC_IRQ_PRIO_1											1
#define NVIC_IRQ_PRIO_2											2
#define NVIC_IRQ_PRIO_3											3
#define NVIC_IRQ_PRIO_4											4
#define NVIC_IRQ_PRIO_5											5
#define NVIC_IRQ_PRIO_6											6
#define NVIC_IRQ_PRIO_7											7
#define NVIC_IRQ_PRIO_8											8
#define NVIC_IRQ_PRIO_9											9
#define NVIC_IRQ_PRIO_10										10
#define NVIC_IRQ_PRIO_11										11
#define NVIC_IRQ_PRIO_12										12
#define NVIC_IRQ_PRIO_13										13
#define NVIC_IRQ_PRIO_14										14
#define NVIC_IRQ_PRIO_15										15


/*Some generic macros*/

#define ENABLE 			1
#define DISABLE 		0
#define SET 			ENABLE
#define RESET 			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET

#define FLAG_RESET		RESET
#define FLAG_SET		SET

/******************************************************************************************
 *Bit position definitions of SPI peripheral
 ******************************************************************************************/
/*
 * Bit position definitions SPI_CR1
 */
#define SPI_CR1_CPHA     				 0
#define SPI_CR1_CPOL      				 1
#define SPI_CR1_MSTR     				 2
#define SPI_CR1_BR   					 3
#define SPI_CR1_SPE     				 6
#define SPI_CR1_LSBFIRST   			 	 7
#define SPI_CR1_SSI     				 8
#define SPI_CR1_SSM      				 9
#define SPI_CR1_RXONLY      		 	10
#define SPI_CR1_DFF     			 	11
#define SPI_CR1_CRCNEXT   			 	12
#define SPI_CR1_CRCEN   			 	13
#define SPI_CR1_BIDIOE     			 	14
#define SPI_CR1_BIDIMODE      			15

/*
 * Bit position definitions SPI_CR2
 */
#define SPI_CR2_RXDMAEN		 			0
#define SPI_CR2_TXDMAEN				 	1
#define SPI_CR2_SSOE				 	2
#define SPI_CR2_FRF						4
#define SPI_CR2_ERRIE					5
#define SPI_CR2_RXNEIE				 	6
#define SPI_CR2_TXEIE					7


/*
 * Bit position definitions SPI_SR
 */
#define SPI_SR_RXNE						0
#define SPI_SR_TXE				 		1
#define SPI_SR_CHSIDE				 	2
#define SPI_SR_UDR					 	3
#define SPI_SR_CRCERR				 	4
#define SPI_SR_MODF					 	5
#define SPI_SR_OVR					 	6
#define SPI_SR_BSY					 	7
#define SPI_SR_FRE					 	8

/******************************************************************************************
 *Bit position definitions of I2C peripheral
 ******************************************************************************************/
/*
 * Bit position definitions I2C_CR1
 */
#define I2C_CR1_PE						0
#define I2C_CR1_NOSTRETCH  				7
#define I2C_CR1_START 					8
#define I2C_CR1_STOP  				 	9
#define I2C_CR1_ACK 				 	10
#define I2C_CR1_SWRST  				 	15

/*
 * Bit position definitions I2C_CR2
 */
#define I2C_CR2_FREQ				 	0
#define I2C_CR2_ITERREN				 	8
#define I2C_CR2_ITEVTEN				 	9
#define I2C_CR2_ITBUFEN 			    10

/*
 * Bit position definitions I2C_OAR1
 */
#define I2C_OAR1_ADD0    				 0
#define I2C_OAR1_ADD71 				 	 1
#define I2C_OAR1_ADD98  			 	 8
#define I2C_OAR1_ADDMODE   			 	15

/*
 * Bit position definitions I2C_SR1
 */

#define I2C_SR1_SB 					 	0
#define I2C_SR1_ADDR 				 	1
#define I2C_SR1_BTF 					2
#define I2C_SR1_ADD10 					3
#define I2C_SR1_STOPF 					4
#define I2C_SR1_RXNE 					6
#define I2C_SR1_TXE 					7
#define I2C_SR1_BERR 					8
#define I2C_SR1_ARLO 					9
#define I2C_SR1_AF 					 	10
#define I2C_SR1_OVR 					11
#define I2C_SR1_TIMEOUT 				14

/*
 * Bit position definitions I2C_SR2
 */
#define I2C_SR2_MSL						0
#define I2C_SR2_BUSY 					1
#define I2C_SR2_TRA 					2
#define I2C_SR2_GENCALL 				4
#define I2C_SR2_DUALF 					7

/*
 * Bit position definitions I2C_CCR
 */
#define I2C_CCR_CCR 					 0
#define I2C_CCR_DUTY 					14
#define I2C_CCR_FS  				 	15

/******************************************************************************************
 *Bit position definitions of USART peripheral
 ******************************************************************************************/

/*
 * Bit position definitions USART_CR1
 */
#define USART_CR1_SBK					0
#define USART_CR1_RWU 					1
#define USART_CR1_RE  					2
#define USART_CR1_TE 					3
#define USART_CR1_IDLEIE 				4
#define USART_CR1_RXNEIE  				5
#define USART_CR1_TCIE					6
#define USART_CR1_TXEIE					7
#define USART_CR1_PEIE 					8
#define USART_CR1_PS 					9
#define USART_CR1_PCE 					10
#define USART_CR1_WAKE  				11
#define USART_CR1_M 					12
#define USART_CR1_UE 					13
#define USART_CR1_OVER8  				15



/*
 * Bit position definitions USART_CR2
 */
#define USART_CR2_ADD   				0
#define USART_CR2_LBDL   				5
#define USART_CR2_LBDIE  				6
#define USART_CR2_LBCL   				8
#define USART_CR2_CPHA   				9
#define USART_CR2_CPOL   				10
#define USART_CR2_STOP   				12
#define USART_CR2_LINEN   				14


/*
 * Bit position definitions USART_CR3
 */
#define USART_CR3_EIE   				0
#define USART_CR3_IREN   				1
#define USART_CR3_IRLP  				2
#define USART_CR3_HDSEL   				3
#define USART_CR3_NACK   				4
#define USART_CR3_SCEN   				5
#define USART_CR3_DMAR  				6
#define USART_CR3_DMAT   				7
#define USART_CR3_RTSE   				8
#define USART_CR3_CTSE   				9
#define USART_CR3_CTSIE   				10
#define USART_CR3_ONEBIT   				11

/*
 * Bit position definitions USART_SR
 */

#define USART_SR_PE        				0
#define USART_SR_FE        				1
#define USART_SR_NE        				2
#define USART_SR_ORE       				3
#define USART_SR_IDLE       			4
#define USART_SR_RXNE        			5
#define USART_SR_TC        				6
#define USART_SR_TXE        			7
#define USART_SR_LBD        			8
#define USART_SR_CTS        			9

#include "stm32f407_gpio_driver.h"
#include "stm32f407_spi_driver.h"
#include "stm32f407_I2C_driver.h"
#include "stm32f407_usart_driver.h"
#include "stm32f407_rcc_driver.h"

#endif /* INC_STM32F407_H_ */
