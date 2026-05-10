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

void enableTimClock(TIM_TypeDef* tim)
{
    if(tim==TIM1) __HAL_RCC_TIM1_CLK_ENABLE();
    if(tim==TIM2) __HAL_RCC_TIM2_CLK_ENABLE();
    if(tim==TIM3) __HAL_RCC_TIM3_CLK_ENABLE();
    if(tim==TIM4) __HAL_RCC_TIM4_CLK_ENABLE();
    if(tim==TIM5) __HAL_RCC_TIM5_CLK_ENABLE();
    if(tim==TIM8) __HAL_RCC_TIM8_CLK_ENABLE();
    if(tim==TIM9) __HAL_RCC_TIM9_CLK_ENABLE();
    if(tim==TIM10) __HAL_RCC_TIM10_CLK_ENABLE();
    if(tim==TIM11) __HAL_RCC_TIM11_CLK_ENABLE();
    if(tim==TIM12) __HAL_RCC_TIM12_CLK_ENABLE();
    if(tim==TIM13) __HAL_RCC_TIM13_CLK_ENABLE();
    if(tim==TIM14) __HAL_RCC_TIM14_CLK_ENABLE();
}

uint32_t getTimerClock(TIM_TypeDef* tim)
{
    uint32_t pclk;
    uint32_t prescaler;

    if(tim==TIM1 || tim==TIM8 || tim==TIM9 || tim==TIM10 || tim==TIM11){
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
    return (tim == TIM1 || tim == TIM8);
}

#endif