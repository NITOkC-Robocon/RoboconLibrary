#pragma once

#if defined(STM32F446xx)
#include "core/System.hpp"

constexpr uint8_t TIMER_COUNT = 12;
extern TIM_TypeDef* timers[TIMER_COUNT];
int timerIndex(TIM_TypeDef* tim);

void enableTimClock(TIM_TypeDef* tim);
uint32_t getTimerClock(TIM_TypeDef* tim);

bool isAdvancedTimer(TIM_TypeDef* tim);

#endif