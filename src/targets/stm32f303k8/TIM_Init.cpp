#include "core/TIM_Manager.hpp"
#include "driver/timer/TIM_EventScheduler.hpp"

#if defined(STM32F303x8)

//割り込みハンドラの定義

extern "C" void TIM1_UP_TIM16_IRQHandler(){

}
extern "C" void TIM2_IRQHandler(){

}
extern "C" void TIM3_IRQHandler(){

}
extern "C" void TIM1_BRK_TIM15_IRQHandler(){

}
extern "C" void TIM1_TRG_COM_TIM17_IRQHandler(){
    TIM_Clock_IRQHandler();
}



void enableTimClock(TIM_TypeDef* tim)
{
    if(tim==TIM1) __HAL_RCC_TIM1_CLK_ENABLE();
    if(tim==TIM2) __HAL_RCC_TIM2_CLK_ENABLE();
    if(tim==TIM3) __HAL_RCC_TIM3_CLK_ENABLE();

    if(tim==TIM6) __HAL_RCC_TIM6_CLK_ENABLE();
    if(tim==TIM7) __HAL_RCC_TIM7_CLK_ENABLE();
    
    if(tim==TIM15) __HAL_RCC_TIM15_CLK_ENABLE();
    if(tim==TIM16) __HAL_RCC_TIM16_CLK_ENABLE();
    if(tim==TIM17) __HAL_RCC_TIM17_CLK_ENABLE();
}

bool isAPB2TIM(TIM_TypeDef* tim)
{
    return (tim==TIM1 || tim==TIM15 || tim==TIM16 || tim==TIM17);
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
    if(tim == TIM2){
        return UINT32_MAX;
    }
    else return UINT16_MAX;
}

IRQn_Type getTIMUpdateIRQn(TIM_TypeDef* tim)
{
    if (tim == TIM1) return TIM1_UP_TIM16_IRQn;
    if (tim == TIM2) return TIM2_IRQn;
    if (tim == TIM3) return TIM3_IRQn;
    if (tim == TIM6) return TIM6_DAC_IRQn;
    if (tim == TIM7) return TIM7_IRQn;
    if (tim == TIM15) return TIM1_BRK_TIM15_IRQn;
    if (tim == TIM16) return TIM1_UP_TIM16_IRQn;
    if (tim == TIM17) return TIM1_TRG_COM_TIM17_IRQn;

    while (1);
}

bool isAdvancedTimer(TIM_TypeDef* tim)
{
    return (tim==TIM1 || tim==TIM15 || tim==TIM16 || tim==TIM17);
}

#endif