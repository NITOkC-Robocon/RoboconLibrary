#include "core/ADC_DAC_Init.hpp"


#if defined(STM32F303x8)

//===== ADC関係 =====

bool adc_initialized[ADC_COUNT] = {};
ADC_HandleTypeDef adc_handle[ADC_COUNT];

int adc_index(ADC_TypeDef* adc)
{
    if(adc == ADC1) return 0;
    if(adc == ADC2) return 1;
    return -1;
}

ADC_HandleTypeDef* getADC_Handle(ADC_TypeDef* adc)
{
    int idx = adc_index(adc);

    if(idx < 0)
    {
        return nullptr;
    }

    return &adc_handle[idx];
}

//ADCクロック有効化
void enable_adc_clock(ADC_TypeDef* adc)
{
    if(adc == ADC1) __HAL_RCC_ADC1_CLK_ENABLE();
    else if(adc == ADC2) __HAL_RCC_ADC2_CLK_ENABLE();
}

//===== DAC関係 =====

bool dac_initialized[DAC_COUNT] = {};
DAC_HandleTypeDef dac_handle[DAC_COUNT] = {};

int dac_index(DAC_TypeDef* dac)
{
    if(dac == DAC1) return 0;
    if(dac == DAC2) return 1;
    return -1;
}

DAC_HandleTypeDef* getDAC_Handle(DAC_TypeDef* dac)
{
    int idx = dac_index(dac);

    if(idx < 0)
    {
        return nullptr;
    }

    return &dac_handle[idx];
}

void enable_dac_clock(DAC_TypeDef* dac)
{
    if(dac == DAC1) __HAL_RCC_DAC1_CLK_ENABLE();
    else if(dac == DAC2) __HAL_RCC_DAC2_CLK_ENABLE();
}

#endif