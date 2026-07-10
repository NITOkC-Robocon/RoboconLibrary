#pragma once

#if defined(STM32F446xx)
extern "C" {
    #include "stm32f4xx_hal.h"
}




#define USBTX PA_2
#define USBRX PA_3

#define LED PA_5


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


//----- Analog 情報 -----
constexpr uint8_t MAX_ADC_PER_PIN = 3;
struct ADCInfo {
    ADC_TypeDef* adc;
    uint32_t channel;
};

struct DACInfo {
    DAC_TypeDef* dac;
    uint32_t channel;
};

//----- TIM 情報 -----
constexpr uint8_t MAX_TIM_PER_PIN = 4;
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

constexpr uint8_t MAX_UART_PER_PIN = 2;
struct UARTInfo {
    USART_TypeDef* uart;
    uint32_t uart_af;
    UART_MODE uart_mode; 
};

//----- I2C 情報 -----
constexpr uint8_t MAX_I2C_PER_PIN = 1;
enum I2C_MODE {
    I2C_SDA,
    I2C_SCL,
    I2C_NONE
};

struct I2CInfo {
    I2C_TypeDef* i2c;
    uint32_t af;
    I2C_MODE mode;   // SDA / SCL
};

//----- ピン情報まとめ -----
struct PinInfo {
    const char* name;
    GPIO_TypeDef* port;
    uint16_t pin;

    // --- ADC/DAC ---
    ADCInfo adc_info[MAX_ADC_PER_PIN];
    DACInfo dac_info;

    // --- TIM ---
    TIMInfo tim_info[MAX_TIM_PER_PIN];

    //--- UART ---
    UARTInfo uart_info[MAX_UART_PER_PIN];

    //--- I2C ---
    I2CInfo i2c_info[MAX_I2C_PER_PIN];  // SDA, SCL
};


// PinMap 配列の宣言
extern const PinInfo PinMap[PIN_MAX];

#endif