/*
 * stm32f407_gpio_driver.c
 *
 *  Created on: Oct 20, 2025
 *      Author: Abijith Radhakrishnan
 */


#include "stm32f407_gpio_driver.h"

void GPIO_Init(GPIO_Handle_t *pGPIOHandle){

	uint32_t temp = 0;

	//Enable clock for that peripheral

	GPIO_PeriClkCtrl(pGPIOHandle->pGPIOx, ENABLE);

	//configure mode of input pin

	if(pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
	//non interrupt mode
		temp = (pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinMode << (2 * pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber)); /*since the each pin takes 2 bits of mode position, pin number * 2 gives corresponding bit position*/
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber);//clearing
		pGPIOHandle->pGPIOx->MODER |= temp;//setting
		temp = 0;

	}else
	{
	//interrupt mode

		if(pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT){
			//Configure FTSR
			EXTI->FTSR |=(1<<pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber);
			//clear corresponding RTSR
			EXTI->RTSR &= ~(1<<pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber);

		}else if(pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT){
			//configure RTSR
			EXTI->RTSR |=(1<<pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber);
			//clear corresponding FTSR
			EXTI->FTSR &= ~(1<<pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber);

		}else if(pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT){
			//configure both FTSR and RTSR
			EXTI->RTSR |=(1<<pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= (1<<pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber);

		}
		//configure GPIO port selection in SYSCGF_EXTICR
		uint8_t temp1 = pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber/4;
		uint8_t temp2 = pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber%4;
		uint8_t portCode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] = portCode <<(temp2*4);

		//Enable exti interrupt delivery using IMR
		EXTI->IMR |= (1<<pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber);

	}
	temp = 0;
	//configure speed
	temp = (pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber)); /*since the each pin takes 2 bits of mode position, pin number * 2 gives corresponding bit position*/
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 <<pGPIOHandle->pGPIOx_PinConfig.GPIO_PinNumber);//clearing
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;
	temp = 0;

	//configure pull up pull down register
	temp = (pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber)); /*since the each pin takes 2 bits of mode position, pin number * 2 gives corresponding bit position*/
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << pGPIOHandle->pGPIOx_PinConfig.GPIO_PinNumber);//clearing
	pGPIOHandle->pGPIOx->PUPDR |= temp;
	temp = 0;

	//configure output type register
	temp = (pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinOPType << (pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber)); /*since the each pin takes 1 bits of mode position, pin number * 1 gives corresponding bit position*/
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->pGPIOx_PinConfig.GPIO_PinNumber);//clearing
	pGPIOHandle->pGPIOx->OTYPER |= temp;
	temp = 0;

	//configure Alternate function register
	if(pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){

		//configure alternate functionality register
		uint8_t temp1,temp2;
		temp1 = pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2)); //clearing
		pGPIOHandle->pGPIOx->AFR[temp1] |=(pGPIOHandle ->pGPIOx_PinConfig.GPIO_PinAltFunMode << (4 * temp2)); /*since the each pin takes 4 bits of mode position, pin number * 4 gives corresponding bit position*/
	}
}
void GPIO_DeInit(GPIO_Regdef_t *pGPIOx){

		if(pGPIOx == GPIOA){
				GPIOA_REG_RESET();
			}else if (pGPIOx == GPIOB){
				GPIOA_REG_RESET();
			}else if (pGPIOx == GPIOC){
				GPIOA_REG_RESET();
			}else if (pGPIOx == GPIOD){
				GPIOA_REG_RESET();
			}else if (pGPIOx == GPIOE){
				GPIOA_REG_RESET();
			}else if (pGPIOx == GPIOF){
				GPIOA_REG_RESET();
			}else if (pGPIOx == GPIOG){
				GPIOA_REG_RESET();
			}else if (pGPIOx == GPIOH){
				GPIOA_REG_RESET();
			}else if (pGPIOx == GPIOI){
				GPIOA_REG_RESET();
			}

}
void GPIO_PeriClkCtrl(GPIO_Regdef_t *pGPIOx, uint8_t EnorDi){

	if(EnorDi == ENABLE){
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_EN();
		}else if (pGPIOx == GPIOB){
			GPIOB_PCLK_EN();
		}else if (pGPIOx == GPIOC){
			GPIOC_PCLK_EN();
		}else if (pGPIOx == GPIOD){
			GPIOD_PCLK_EN();
		}else if (pGPIOx == GPIOE){
			GPIOE_PCLK_EN();
		}else if (pGPIOx == GPIOF){
			GPIOF_PCLK_EN();
		}else if (pGPIOx == GPIOG){
			GPIOG_PCLK_EN();
		}else if (pGPIOx == GPIOH){
			GPIOH_PCLK_EN();
		}else if (pGPIOx == GPIOI){
			GPIOI_PCLK_EN();
		}
	}
	else
	{
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_DI();
		}else if (pGPIOx == GPIOB){
			GPIOB_PCLK_DI();
		}else if (pGPIOx == GPIOC){
			GPIOB_PCLK_DI();
		}else if (pGPIOx == GPIOD){
			GPIOB_PCLK_DI();
		}else if (pGPIOx == GPIOE){
			GPIOB_PCLK_DI();
		}else if (pGPIOx == GPIOF){
			GPIOB_PCLK_DI();;
		}else if (pGPIOx == GPIOG){
			GPIOB_PCLK_DI();
		}else if (pGPIOx == GPIOH){
			GPIOB_PCLK_DI();
		}else if (pGPIOx == GPIOI){
			GPIOB_PCLK_DI();
		}
	}

}
uint8_t GPIO_ReadFrmInptPin(GPIO_Regdef_t *pGPIOx, uint8_t PinNumber){

	uint8_t value;
	value = (uint8_t)( pGPIOx->IDR >> PinNumber ) & 0x00000001;
	return value;

}
uint16_t GPIO_ReadFrmInptPort(GPIO_Regdef_t *pGPIOx){

	uint16_t value;
	value = pGPIOx->IDR;
	return value;
}
void GPIO_WrtToOutputPin(GPIO_Regdef_t *pGPIOx, uint8_t PinNumber,uint8_t Value){

	if(Value == GPIO_PIN_SET){
		pGPIOx->ODR |= (1 << PinNumber);

	}else{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}

}
void GPIO_WrtToOutputPort(GPIO_Regdef_t *pGPIOx,uint16_t Value){

	pGPIOx->ODR = Value;

}
void GPIO_ToggleOutputPin(GPIO_Regdef_t *pGPIOx, uint8_t PinNumber){

	pGPIOx->ODR ^= (1<<PinNumber);

}
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t EnorDi){

	if(EnorDi == ENABLE){

		if(IRQNumber <= 31){
			//ISER0 register
			*NVIC_ISER0 |= (1<<IRQNumber);

		}else if (IRQNumber > 31 && IRQNumber < 64){
			//ISER1 register
			*NVIC_ISER1 |= (1<< (IRQNumber%32) );

		}else if (IRQNumber >= 64 && IRQNumber < 96){
			//ISER2 register
			*NVIC_ISER2 |= (1<< (IRQNumber%64) );
		}
	}else{

		if(IRQNumber <= 31){
			//ISCR0 register
			*NVIC_ICER0 |= (1<<IRQNumber);

		}else if (IRQNumber > 31 && IRQNumber < 64){
			//ISCR1 register
			*NVIC_ICER1 |= (1<< (IRQNumber%32) );

		}else if (IRQNumber >= 64 && IRQNumber < 96){
			//ISCR2 register
			*NVIC_ICER2 |= (1<< (IRQNumber%64) );
		}
	}

}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){

	//finding out IPR register
	uint8_t iprx = IRQNumber/4;
	uint8_t iprxSection = IRQNumber % 4;
	uint8_t shiftAmount = (8 * iprxSection + (8 - NO_PR_BITS_IMPLEMENTED));
	*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << (8* shiftAmount));

}

void GPIO_IRQHandling(uint8_t PinNumber){

	//clear EXTI PR (pending register) register of corresponding pin number
	if(EXTI->PR & (1 << PinNumber)){
		//clear
		EXTI->PR |= (1 << PinNumber);
	}
}
