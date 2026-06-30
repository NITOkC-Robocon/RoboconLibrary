#pragma once

#include "core/PinMap.hpp"
#include "core/ADC_DAC_Init.hpp"


class AnalogIn {
private:
    PinName pinname;

    ADC_HandleTypeDef* hadc = nullptr;
    ADC_TypeDef* adc_instance = nullptr;
    uint32_t channel = 0;

    bool initialized = false;
    void init();

public:
    AnalogIn(PinName pin);

    uint16_t read_u16();

    float read();
};