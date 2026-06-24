#include "driver/analog/AnalogIn.hpp"

#include "core/System.hpp"


AnalogIn::AnalogIn(PinName pin)
{
    pinname = pin;

    for(uint8_t i = 0; i < MAX_ADC_PER_PIN; i++)
    {
        if(PinMap[pinname].adc_info[i].adc != nullptr)
        {
            adc_instance = PinMap[pinname].adc_info[i].adc;
            channel      = PinMap[pinname].adc_info[i].channel;
            break;
        }
    }
}

void AnalogIn::init()
{
    if(initialized) return;
    MCU_Init();

    if(adc_instance == nullptr)
    {
        while(1);
    }

    enableGpioClock(PinMap[pinname].port);

    GPIO_InitTypeDef GPIO_InitStruct{};
    GPIO_InitStruct.Pin  = PinMap[pinname].pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(PinMap[pinname].port, &GPIO_InitStruct);

    hadc = getADC_Handle(adc_instance);

    int index = adc_index(adc_instance);
    if(index < 0)
    {
        while(1);
    }

    if(!adc_initialized[index])
    {
        enable_adc_clock(adc_instance);

        hadc->Instance = adc_instance;

        hadc->Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV4;
        hadc->Init.Resolution            = ADC_RESOLUTION_12B;
        hadc->Init.DataAlign             = ADC_DATAALIGN_RIGHT;

        hadc->Init.ScanConvMode          = DISABLE;
        hadc->Init.ContinuousConvMode    = DISABLE;
        hadc->Init.DiscontinuousConvMode = DISABLE;

        hadc->Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
        hadc->Init.NbrOfConversion       = 1;

        if(HAL_ADC_Init(hadc) != HAL_OK) while(1);

        //if(HAL_ADCEx_Calibration_Start(hadc, ADC_SINGLE_ENDED) != HAL_OK) while(1);

        adc_initialized[index] = true;
    }

    initialized = true;
}

uint16_t AnalogIn::read_u16()
{
    init();

    ADC_ChannelConfTypeDef sConfig{};

    sConfig.Channel      = channel;
    sConfig.Rank         = 1;
    sConfig.SamplingTime = ADC_SamplingTime;

    if(HAL_ADC_ConfigChannel(hadc, &sConfig) != HAL_OK)
    {
        while(1);
    }

    HAL_ADC_Start(hadc);

    if(HAL_ADC_PollForConversion(hadc, 10) != HAL_OK)
    {
        while(1);
    }

    uint32_t value = HAL_ADC_GetValue(hadc);

    HAL_ADC_Stop(hadc);

    return static_cast<uint16_t>(value << 4);
}

float AnalogIn::read()
{
    return read_u16() / 65535.0f;
}