#pragma once

#include "core/PinMap.hpp"


class DigitalIn{
private:
    GPIO_TypeDef* port;
    uint16_t      pin;
    uint32_t pin_pull;

    mutable bool initialized = false;
    void class_initialized() const;

public:
    DigitalIn(PinName pinName, PinMode pull);

    uint8_t read() const;
    void mode(PinMode mode);

    operator int() const {
        return read();
    }
};
