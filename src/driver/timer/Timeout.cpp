#include "driver/timer/Timeout.hpp"
#include "driver/timer/Clock.hpp"

void Timeout::attach_ms(Callback cb, uint32_t period_ms)
{
    attach_us(cb, period_ms * 1000);
}

void Timeout::attach_us(Callback cb, uint32_t period_us)
{
    callback = cb;
    period = period_us;

    uint32_t now = TIM_Clock::get_counter();
    next = now + period;

    isactive = true;

    TIM_EventScheduler::add(this);
}

void Timeout::active()
{
    next = TIM_Clock::get_counter() + period;
    isactive = true;
    TIM_EventScheduler::add(this);
}

void Timeout::detach()
{
    isactive = false;
    TIM_EventScheduler::remove(this);
}

void Timeout::fire()
{
    if(callback) callback();

    isactive = false;
    TIM_EventScheduler::remove(this);
}