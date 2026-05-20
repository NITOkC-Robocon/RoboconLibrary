#pragma once

#if defined(STM32F303x8)
#include "core/System.hpp"

constexpr uint8_t TIMER_COUNT = 6;
extern TIM_TypeDef* timers[TIMER_COUNT];

int timerIndex(TIM_TypeDef* tim);

#endif