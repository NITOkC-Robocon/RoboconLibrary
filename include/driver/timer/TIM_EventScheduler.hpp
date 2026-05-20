#pragma once

#include "core/System.hpp"
#include "TIM_Events.hpp"


#define MAX_EVENTS 16

class TIM_EventScheduler {
    friend void TIM_Clock_IRQHandler();
public:
    static void ThisClass_init();

    static void add(TIM_Event* ticker);
    static void remove(TIM_Event* ticker);

private:
    static void dispatch();
    static void schedule_next();

    static TIM_Event* events[MAX_EVENTS];
    static uint8_t count;
};

void TIM_Clock_IRQHandler();
