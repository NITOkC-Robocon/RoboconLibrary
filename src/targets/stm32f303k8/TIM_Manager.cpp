#include "core/TIM_Manager.hpp"

#if defined(STM32F303x8)

TIM_TypeDef* timers[6] =
{
    TIM1,TIM2,TIM3,
    TIM15,TIM16,TIM17
};

int timerIndex(TIM_TypeDef* tim)
{
    for(int i=0;i<TIMER_COUNT;i++)
    {
        if(timers[i]==tim) return i;
    }

    return -1;
}

#endif