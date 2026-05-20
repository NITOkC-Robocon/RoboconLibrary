#include "core/TIM_Init.hpp"

#if defined(STM32F446xx)

void enableTimClock(TIM_TypeDef* tim)
{
    if(tim==TIM1) __HAL_RCC_TIM1_CLK_ENABLE();
    if(tim==TIM2) __HAL_RCC_TIM2_CLK_ENABLE();
    if(tim==TIM3) __HAL_RCC_TIM3_CLK_ENABLE();
    if(tim==TIM4) __HAL_RCC_TIM4_CLK_ENABLE();
    if(tim==TIM5) __HAL_RCC_TIM5_CLK_ENABLE();
    if(tim==TIM6) __HAL_RCC_TIM6_CLK_ENABLE();
    if(tim==TIM6) __HAL_RCC_TIM7_CLK_ENABLE();
    if(tim==TIM8) __HAL_RCC_TIM8_CLK_ENABLE();
    if(tim==TIM9) __HAL_RCC_TIM9_CLK_ENABLE();
    if(tim==TIM10) __HAL_RCC_TIM10_CLK_ENABLE();
    if(tim==TIM11) __HAL_RCC_TIM11_CLK_ENABLE();
    if(tim==TIM12) __HAL_RCC_TIM12_CLK_ENABLE();
    if(tim==TIM13) __HAL_RCC_TIM13_CLK_ENABLE();
    if(tim==TIM14) __HAL_RCC_TIM14_CLK_ENABLE();
}

bool isAPB2TIM(TIM_TypeDef* tim)
{
    return (tim==TIM1 || tim==TIM8 || tim==TIM9 || tim==TIM10 || tim==TIM11);
}

uint32_t getTimerClock(TIM_TypeDef* tim)
{
    uint32_t pclk;
    uint32_t ppre;

    if(isAPB2TIM(tim)){
        pclk = HAL_RCC_GetPCLK2Freq();
        ppre = (RCC->CFGR & RCC_CFGR_PPRE2) >> 13;
    }
    else
    {
        pclk = HAL_RCC_GetPCLK1Freq();
        ppre = (RCC->CFGR & RCC_CFGR_PPRE1) >> 10;
    }

    return (ppre < 4) ? pclk : pclk * 2;
}

uint32_t getTIMMaxCount(TIM_TypeDef* tim)
{
    if(tim == TIM2 || tim == TIM5){
        return UINT32_MAX;
    }
    else return UINT16_MAX;
}

IRQn_Type getTIMUpdateIRQn(TIM_TypeDef* tim)
{
    if (tim == TIM1) return TIM1_UP_TIM10_IRQn;
    if (tim == TIM2) return TIM2_IRQn;
    if (tim == TIM3) return TIM3_IRQn;
    if (tim == TIM4) return TIM4_IRQn;
    if (tim == TIM5) return TIM5_IRQn;
    if (tim == TIM6) return TIM6_DAC_IRQn;
    if (tim == TIM7) return TIM7_IRQn;
    if (tim == TIM8) return TIM8_UP_TIM13_IRQn;
    if (tim == TIM9) return TIM1_BRK_TIM9_IRQn;
    if (tim == TIM10) return TIM1_UP_TIM10_IRQn;
    if (tim == TIM11) return TIM1_TRG_COM_TIM11_IRQn;
    if (tim == TIM12) return TIM8_BRK_TIM12_IRQn;
    if (tim == TIM13) return TIM8_UP_TIM13_IRQn;
    if (tim == TIM14) return TIM8_TRG_COM_TIM14_IRQn;

    while (1);
}

bool isAdvancedTimer(TIM_TypeDef* tim)
{
    return (tim == TIM1 || tim == TIM8);
}

#endif