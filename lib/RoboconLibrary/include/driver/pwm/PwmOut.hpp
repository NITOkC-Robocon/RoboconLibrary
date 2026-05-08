#pragma once

#include "core/PinMap.hpp"
#include "core/System.hpp"
#include "core/TIM_Manager.hpp"

#include <cstdint>

 
class PwmOut
{
private:
    const PinInfo* info;

    GPIO_TypeDef* port;
    uint16_t pin;

    TIM_TypeDef* tim = nullptr;
    uint32_t channel = 0;


    uint32_t period = 0;

    uint32_t arr = 0;

    static bool channel_used[TIMER_COUNT][4];

    mutable bool initialized = false;
    void class_initialized();

    void enableGpioClock(GPIO_TypeDef* port);

public:
    PwmOut(PinName pinName);

    TIM_HandleTypeDef htim;

    void period_us(uint32_t us);
    void period_ms(uint32_t ms);
    void pulsewidth_ticks(uint32_t ticks);
    void pulsewidth(float sec);
    void pulsewidth_us(uint32_t us);
    void write(float duty);
};


class Servo 
{
private:
    PwmOut pwm;

public:
    Servo(PinName pin);

    uint32_t min_us = 500;
    uint32_t max_us = 2500;

    void period_us(uint32_t us);
    void period_ms(uint32_t ms);
    void setPulseRange(uint32_t min, uint32_t max);
    void pulsewidth_us(uint32_t us);
};