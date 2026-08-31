#include "driver/timer/Ticker.hpp"
#include "driver/timer/Clock.hpp"

void Ticker::attach_ms(Callback cb, uint32_t period_ms)
{
    attach_us(cb, period_ms * 1000);
}

void Ticker::attach_us(Callback cb, uint32_t period_us)
{
    callback = cb;
    period = period_us;

    uint32_t now = TIM_Clock::get_counter();
    next = now + period;

    isactive = true;

    TIM_EventScheduler::add(this);
}

void Ticker::active()
{
    next = TIM_Clock::get_counter() + period;
    isactive = true;
    TIM_EventScheduler::add(this);
}

void Ticker::detach()
{
    isactive = false;
    TIM_EventScheduler::remove(this);
}

void Ticker::fire()
{
    if(callback) callback();

    if(period == 0) {
        return;
    }

    while((int32_t)(TIM_Clock::get_counter() - next) >= 0) {
        next += period;
    }
}