#pragma once

#include "core/PinMap.hpp"
extern "C" {
    #include "stm32f4xx_hal.h"
}

#ifndef INTERRUPTIN_H
#define INTERRUPTIN_H


class InterruptIn {
private:
    GPIO_TypeDef* port;
    uint16_t pin;
    uint32_t pull_mode;
    int pin_number;

    mutable bool initialized = false;
    void class_initialized();
    void init_exti();

    void (*rise_func)(void*);
    void* rise_obj;
    void (*fall_func)(void*);
    void* fall_obj;

public:
    InterruptIn(PinName pinName, PinMode pull = PullNone);

    static InterruptIn* instances[16];
    
    void mode(PinMode mode);
    void rise(void* obj, void (*func)(void*));
    void fall(void* obj, void (*func)(void*));
    int read();

    void handle_interrupt();
};

#endif