#pragma once

#include "core/System.hpp"
#include "core/PinMap.hpp"
#include "core/ADC_DAC_Init.hpp"

extern bool adc_initialized[ADC_COUNT];

class AnalogIn {
private:
    PinName pinname;

    ADC_HandleTypeDef* hadc = nullptr;
    ADC_TypeDef* adc_instance = nullptr;
    uint32_t channel = 0;

    bool initialized = false;
    void init();

public:
    explicit AnalogIn(PinName pin);

    uint16_t read_u16();

    float read();
};