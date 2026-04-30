#pragma once

extern "C" {
    #include "stm32f4xx_hal.h"
}

#define USBTX PA_2
#define USBRX PA_3

enum PinMode{
    PullNone,
    PullUp,
    PullDown,

    PULL_MAX
};

extern const uint32_t PinPull[PULL_MAX];

#include <cstdint>

// -----------------------------------
// ピン名の列挙
// -----------------------------------
enum PinName {
    // Port A
    PA_0, PA_1, PA_2, PA_3, PA_4, PA_5, PA_6, PA_7, PA_8, PA_9, PA_10, PA_11, PA_12, PA_13, PA_14, PA_15,

    // Port B (PB11除外)
    PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7, PB_8, PB_9, PB_10, PB_12, PB_13, PB_14, PB_15,

    // Port C
    PC_0, PC_1, PC_2, PC_3, PC_4, PC_5, PC_6, PC_7, PC_8, PC_9, PC_10, PC_11, PC_12, PC_13, PC_14, PC_15,

    // Port D
    PD_2,

    // 最大値
    PIN_MAX
};

// -----------------------------------
// ピン情報構造体
// -----------------------------------
struct PinInfo {
    const char* name;
    GPIO_TypeDef* port;
    uint16_t pin;

    // --- TIM ---
    TIM_TypeDef* tim[2];
    uint32_t channel[2];
    uint32_t af[2];
    uint8_t tim_count;

    //--- UART ---
    USART_TypeDef* uart[2];
    uint32_t uart_af[2];
    uint8_t uart_count;
};

// PinMap 配列の宣言
extern const PinInfo PinMap[PIN_MAX];