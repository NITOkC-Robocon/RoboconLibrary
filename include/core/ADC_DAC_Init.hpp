#pragma once

#if defined(STM32F446xx)
extern "C" {
    #include "stm32f4xx_hal.h"
}
//===== ADC用 ======

constexpr uint8_t ADC_COUNT = 3;
extern bool adc_initialized[ADC_COUNT];

extern ADC_HandleTypeDef adc_handle[ADC_COUNT];
constexpr uint32_t ADC_SamplingTime = ADC_SAMPLETIME_84CYCLES;

//===== DAC用 ======

const bool DefaultBufferExistence = true;

constexpr uint8_t DAC_COUNT = 1;
extern bool dac_initialized[DAC_COUNT];

extern DAC_HandleTypeDef dac_handle[DAC_COUNT];


#elif defined(STM32F303x8) 
extern "C" {
    #include "stm32f3xx_hal.h"
}
//===== ADC用 ======

constexpr uint8_t ADC_COUNT = 2;
extern bool adc_initialized[ADC_COUNT];

extern ADC_HandleTypeDef adc_handle[ADC_COUNT];
constexpr uint32_t ADC_SamplingTime = ADC_SAMPLETIME_181CYCLES_5;

//===== DAC用 ======

const bool DefaultBufferExistence = false;

constexpr uint8_t DAC_COUNT = 2;
extern bool dac_initialized[DAC_COUNT];

extern DAC_HandleTypeDef dac_handle[DAC_COUNT];

#endif

//===== ADC関係 ======

int adc_index(ADC_TypeDef* adc);
ADC_HandleTypeDef* getADC_Handle(ADC_TypeDef* adc);
void enable_adc_clock(ADC_TypeDef* adc);

//===== DAC関係 =====

int dac_index(DAC_TypeDef* dac);
DAC_HandleTypeDef* getDAC_Handle(DAC_TypeDef* dac);
void enable_dac_clock(DAC_TypeDef* dac);

