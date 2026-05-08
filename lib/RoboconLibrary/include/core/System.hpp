#pragma once

#include <stdint.h>
#include <stdbool.h>

//target_select

#if defined(STM32F446xx)
extern "C" {
    #include "stm32f4xx_hal.h"
}

constexpr uint32_t GPIO_SPEED_MAX = GPIO_SPEED_FREQ_VERY_HIGH;
#elif defined(STM32F303x8) 
extern "C" {
    #include "stm32f3xx_hal.h"
}

constexpr uint32_t GPIO_SPEED_MAX = GPIO_SPEED_FREQ_HIGH;

#endif


// タイマー
typedef struct {
    uint32_t last;
    bool firstCall;
} TaskTimer;

/**
 * @brief " マイコンの初期化 "
 * 
 * １度しか実行されない
 */
void MCU_Init();
void Error_Handler(void);

IRQn_Type getExtiIRQ(uint8_t pin_number);
