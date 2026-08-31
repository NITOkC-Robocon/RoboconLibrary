#include "driver/timer/TIM_EventScheduler.hpp"

#include "driver/timer/Clock.hpp"

namespace {
inline bool is_due(uint32_t now, uint32_t next) {
    return (int32_t)(now - next) >= 0;
}

inline bool is_earlier(uint32_t a, uint32_t b) {
    return (int32_t)(a - b) < 0;
}
}

TIM_Event* TIM_EventScheduler::events[MAX_EVENTS] = {};
uint8_t TIM_EventScheduler::count = 0;

void TIM_EventScheduler::ThisClass_init()
{
    static bool initialized = false;
    if(initialized) return;

    TIM_Clock::init();
    TIM_Clock::start();

    __HAL_TIM_ENABLE_IT(&TIM_Clock::handle(), TIM_IT_CC1);

    initialized = true;
}

void TIM_EventScheduler::add(TIM_Event* ticker)
{
    ThisClass_init();

    __HAL_TIM_ENABLE_IT(&TIM_Clock::handle(), TIM_IT_CC1);

    if(count >= MAX_EVENTS) return;

    for(uint8_t i = 0; i < count; i++) {
        if(events[i] == ticker) return;
    }

    events[count++] = ticker;

    schedule_next();
}

void TIM_EventScheduler::remove(TIM_Event* ticker)
{
    ThisClass_init();
    for(uint8_t i = 0; i < count; i++)
    {
        if(events[i] == ticker)
        {
            events[i] = events[count - 1];
            count--;
            break;
        }
    }

    schedule_next();
}

void TIM_EventScheduler::dispatch()
{   
    const uint32_t now = TIM_Clock::get_counter();

    uint8_t i = 0;
    while(i < count)
    {
        TIM_Event* e = events[i];

        if(e->isactive && is_due(now, e->next)) {
            e->fire();
            // e->fire() may remove or reorder events[]; if the current slot still
            // contains the same pointer, advance index. If it was removed and
            // replaced by the last element, do not increment i so the moved
            // element at events[i] gets processed next.
            if(events[i] == e) {
                i++;
            }
        } else {
            i++;
        }
    }

    schedule_next();
}

void TIM_EventScheduler::schedule_next()
{
    if(count == 0) {
        __HAL_TIM_DISABLE_IT(&TIM_Clock::handle(), TIM_IT_CC1);
        return;
    }

    TIM_Event* nextEvent = nullptr;

    for(uint8_t i = 0; i < count; i++)
    {
        if(!events[i]->isactive) continue;

        if(nextEvent == nullptr || is_earlier(events[i]->next, nextEvent->next))
        {
            nextEvent = events[i];
        }
    }

    if(nextEvent)
    {
        uint32_t now = TIM_Clock::get_counter();
        uint32_t target = nextEvent->next;

        if((int32_t)(target - now) <= 0) {
            target = now + 1u;
            nextEvent->next = target;
        }

        __HAL_TIM_SET_COMPARE(&TIM_Clock::handle(), TIM_CHANNEL_1, target);
    }
}


//共通ハンドラ

void TIM_Clock_IRQHandler()
{
    if(__HAL_TIM_GET_FLAG(&TIM_Clock::handle(), TIM_FLAG_UPDATE))
    {
        if(__HAL_TIM_GET_IT_SOURCE(&TIM_Clock::handle(), TIM_IT_UPDATE))
        {
            __HAL_TIM_CLEAR_IT(&TIM_Clock::handle(), TIM_IT_UPDATE);

            TIM_Clock::overflow_count++;
        }
    }

    if(__HAL_TIM_GET_FLAG(&TIM_Clock::handle(), TIM_FLAG_CC1))
    {
        if(__HAL_TIM_GET_IT_SOURCE(&TIM_Clock::handle(), TIM_IT_CC1))
        {
            __HAL_TIM_CLEAR_IT(&TIM_Clock::handle(), TIM_IT_CC1);

            TIM_EventScheduler::dispatch();
        }
    }
}