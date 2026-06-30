#pragma once

#include "core/PinMap.hpp"
#include "core/ADC_DAC_Init.hpp"

class AnalogOut {
private:
    PinName pinname;

    DAC_HandleTypeDef* hdac = nullptr;
    DAC_TypeDef* dac_instance = nullptr;
    uint32_t channel = 0;

    uint32_t DAC_OUTPUTBUFFER_EXISTENCE;

    bool initialized = false;
    void init();

public:
    AnalogOut(PinName pin);

    void set_buffer_extence(bool buffer = DefaultBufferExistence);

    void write(float value);
    void write_u16(uint16_t value);
};
