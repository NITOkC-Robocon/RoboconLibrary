#pragma once

#include "core/System.hpp"

class TIM_Event {
public:
    virtual void fire() = 0;

    uint32_t next = 0;
    bool isactive = false;

    virtual ~TIM_Event() = default;

private:
};