#pragma once

#include "core/PinMap.hpp"


class DigitalOut
{
private:
    GPIO_TypeDef* port;
    uint16_t      pin;

    mutable bool initialized = false;
    void class_initialized() const; 

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
