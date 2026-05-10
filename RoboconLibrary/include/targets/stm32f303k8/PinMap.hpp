#pragma once

#if defined(STM32F303x8)
extern "C" {
    #include "stm32f3xx_hal.h"
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


// -----------------------------------
// ピン名の列挙
// -----------------------------------
enum PinName {
    // Port A
    PA_0, PA_1, PA_2, PA_3, PA_4, PA_5, PA_6, PA_7, PA_8, PA_9, PA_10, PA_11, PA_12,

    // Port B (PB2除外)
    PB_0, PB_1, PB_3, PB_4, PB_5, PB_6, PB_7,

    // Port F
    PD_0, PF_1,

    // 最大値
    PIN_MAX
};


//----- TIM 情報 -----
constexpr uint8_t MAX_TIM_PER_PIN = 3;
struct TIMInfo {
    TIM_TypeDef* tim;
    uint32_t channel;
    uint32_t af;
};

//----- UART 情報 -----
enum UART_MODE {
    TX,
    RX,
    BOTH,
    NONE
};

constexpr uint8_t MAX_UART_PER_PIN = 1;
struct UARTInfo {
    USART_TypeDef* uart;
    uint32_t uart_af;
    UART_MODE uart_mode; 
};

//----- ピン情報まとめ -----
struct PinInfo {
    const char* name;
    GPIO_TypeDef* port;
    uint16_t pin;

    // --- TIM ---
    TIMInfo tim_info[MAX_TIM_PER_PIN];

    //--- UART ---
    UARTInfo uart_info[MAX_UART_PER_PIN];
};


// PinMap 配列の宣言
extern const PinInfo PinMap[PIN_MAX];

#endif