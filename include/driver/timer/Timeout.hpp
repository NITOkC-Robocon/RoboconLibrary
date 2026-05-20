#pragma once

#include "core/System.hpp"
#include "TIM_Events.hpp"
#include "TIM_EventScheduler.hpp"

class Timeout : public TIM_Event {
public:
    using Callback = void(*)();

    Timeout() = default;
    void attach_ms(Callback cb, uint32_t period_ms);
    void attach_us(Callback cb, uint32_t period_us);
    void active();
    void detach();

    void fire() override;
private:
    Callback callback = nullptr;
    uint32_t period = 0;
};