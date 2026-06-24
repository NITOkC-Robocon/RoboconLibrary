#pragma once


#if defined(STM32F446xx)
extern "C" {
    #include "stm32f4xx_hal.h"
}

constexpr uint8_t TIMER_COUNT = 12;
extern TIM_TypeDef* timers[TIMER_COUNT];

int timerIndex(TIM_TypeDef* tim);

#elif defined(STM32F303x8)
extern "C" {
    #include "stm32f3xx_hal.h"
}

constexpr uint8_t TIMER_COUNT = 6;
extern TIM_TypeDef* timers[TIMER_COUNT];

int timerIndex(TIM_TypeDef* tim);

#endif