#pragma once

#include "core/PinMap.hpp"
#include "core/System.hpp"
extern "C" {
    #include "stm32f4xx_hal.h"
}

class DigitalOut
{
private:
    GPIO_TypeDef* port;
    uint16_t      pin;

    mutable bool initialized = false;
    void class_initialized() const;

    void enableClock(GPIO_TypeDef* port) const;  

public:
    DigitalOut(PinName pinName);
    void write(uint8_t value);
    int read() const;
    void toggle();
    void high();
    void low();

    DigitalOut& operator = (int value){
        write(value);
        return *this;
    }

    operator int() const {
        return read();
    }
};
