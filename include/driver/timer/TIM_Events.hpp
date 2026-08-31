#pragma once

#include "core/System.hpp"

class TIM_Event {
public:
    virtual void fire() = 0;

    volatile uint32_t next = 0;
    volatile bool isactive = false;

    virtual ~TIM_Event() = default;

private:
};