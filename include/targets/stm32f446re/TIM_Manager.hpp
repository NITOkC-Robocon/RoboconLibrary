#pragma once

#if defined(STM32F446xx)
#include "core/System.hpp"

constexpr uint8_t TIMER_COUNT = 12;
extern TIM_TypeDef* timers[TIMER_COUNT];

int timerIndex(TIM_TypeDef* tim);

#endif