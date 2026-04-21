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
//uint32_t get_time_ms();
//void wait_ms(uint32_t ms);
void Error_Handler(void);


