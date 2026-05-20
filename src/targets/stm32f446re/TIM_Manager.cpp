#include "core/TIM_Manager.hpp"

#if defined(STM32F446xx)

TIM_TypeDef* timers[12] =
{
    TIM1,TIM2,TIM3,TIM4,TIM5,
    TIM8,
    TIM9,TIM10,TIM11,
    TIM12,TIM13,TIM14
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