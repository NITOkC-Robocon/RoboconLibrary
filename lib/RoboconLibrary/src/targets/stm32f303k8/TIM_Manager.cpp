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

void enableTimClock(TIM_TypeDef* tim)
{
    if(tim==TIM1) __HAL_RCC_TIM1_CLK_ENABLE();
    if(tim==TIM2) __HAL_RCC_TIM2_CLK_ENABLE();
    if(tim==TIM3) __HAL_RCC_TIM3_CLK_ENABLE();
    
    if(tim==TIM15) __HAL_RCC_TIM15_CLK_ENABLE();
    if(tim==TIM16) __HAL_RCC_TIM16_CLK_ENABLE();
    if(tim==TIM17) __HAL_RCC_TIM17_CLK_ENABLE();
}

uint32_t getTimerClock(TIM_TypeDef* tim)
{
    uint32_t pclk;
    uint32_t prescaler;

    if(tim==TIM1 || tim==TIM15 || tim==TIM16 || tim==TIM17){
        pclk = HAL_RCC_GetPCLK2Freq();
        prescaler = (RCC->CFGR & RCC_CFGR_PPRE2) >> 13;
    }
    else
    {
        pclk = HAL_RCC_GetPCLK1Freq();
        prescaler = (RCC->CFGR & RCC_CFGR_PPRE1) >> 10;
    }

    if(prescaler < 4) return pclk;
    else return pclk * 2;
}

bool isAdvancedTimer(TIM_TypeDef* tim)
{
    return (tim==TIM1 || tim==TIM15 || tim==TIM16 || tim==TIM17);
}

#endif