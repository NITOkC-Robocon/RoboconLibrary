#pragma once

#include "core/PinMap.hpp"
#include "core/System.hpp"

class DigitalOut
{
private:
    GPIO_TypeDef* port;
    uint16_t      pin;

    void enableClock(GPIO_TypeDef* port);  

public:
    DigitalOut(PinName pinName);
    void write(uint8_t value);
    int read();
    void toggle();
    void high();
    void low();

    DigitalOut& operator = (int value){
        write(value);
        return *this;
    }

    operator int(){
        return read();
    }
};
