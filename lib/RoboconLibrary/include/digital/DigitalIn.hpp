#pragma once

#include "core/PinMap.hpp"
#include "core/System.hpp"

class DigitalIn{
private:
    GPIO_TypeDef* port;
    uint16_t      pin;

    void enableClock(GPIO_TypeDef* port);

public:
    DigitalIn(PinName pinName, uint32_t pull = GPIO_NOPULL);
    uint8_t read();
    void mode(PinMode mode);

    operator int(){
        return read();
    }
};
