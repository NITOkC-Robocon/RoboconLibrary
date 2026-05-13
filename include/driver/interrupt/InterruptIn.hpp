#pragma once

#include "core/PinMap.hpp"
#include "core/System.hpp"


#ifndef INTERRUPTIN_H
#define INTERRUPTIN_H


class InterruptIn {
    friend void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
private:
    static InterruptIn* instances[16];

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

    void handle_interrupt();
public:
    InterruptIn(PinName pinName, PinMode pull = PullNone);
    
    void mode(PinMode mode);
    void rise(void* obj, void (*func)(void*));
    void fall(void* obj, void (*func)(void*));
    int read();
};

#endif