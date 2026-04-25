#pragma once

#include <stdint.h>
#include <stdbool.h>
extern "C" {
    #include "stm32f4xx_hal.h"
}

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


