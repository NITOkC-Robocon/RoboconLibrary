#pragma once

#if defined(STM32F446xx)
extern "C" {
    #include "stm32f4xx_hal.h"
}
TIM_TypeDef* const TIM_instance = TIM5;

#elif defined(STM32F303x8) 
extern "C" {
    #include "stm32f3xx_hal.h"
}
TIM_TypeDef* const TIM_instance = TIM17;

#endif


void enableTimClock(TIM_TypeDef* tim);

bool isAPB2TIM(TIM_TypeDef* tim);

uint32_t getTimerClock(TIM_TypeDef* tim);

uint32_t getTIMMaxCount(TIM_TypeDef* tim);

IRQn_Type getTIMUpdateIRQn(TIM_TypeDef* tim);

bool isAdvancedTimer(TIM_TypeDef* tim);
