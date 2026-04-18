#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"

// タイマー
typedef struct {
    uint32_t last;
    bool firstCall;
} TaskTimer;

void MCU_Init();
void Error_Handler(void);
bool sleep_for_ms(TaskTimer *t, uint32_t period);


