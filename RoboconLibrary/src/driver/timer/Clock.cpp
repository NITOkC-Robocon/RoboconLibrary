// Clock.cpp
#include "driver/timer/Clock.hpp"

void Clock::init() {
    static bool initialized = false;
    if (initialized) return;
    
    MCU_Init();
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    prev = DWT->CYCCNT;

    initialized = true;
}

uint64_t Clock::timer_accumulated = 0;
uint32_t Clock::prev = 0;

void Clock::Update() {
    uint32_t now = DWT->CYCCNT;

    uint32_t dt = now - prev;
    prev = now;
    timer_accumulated += dt;
}

uint64_t Clock::now()
{
    uint32_t primask = __get_PRIMASK();
    __disable_irq();

    uint32_t now = DWT->CYCCNT;
    uint64_t t = timer_accumulated + (uint32_t)(now - prev);

    __set_PRIMASK(primask);
    return t;
}