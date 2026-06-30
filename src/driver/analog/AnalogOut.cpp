#include "driver/analog/AnalogOut.hpp"

#include "core/System.hpp"


AnalogOut::AnalogOut(PinName pin)
{
    pinname = pin;

    dac_instance = PinMap[pinname].dac_info.dac;
    channel      = PinMap[pinname].dac_info.channel;

    set_buffer_extence();
}

void AnalogOut::init()
{
    if(initialized) return;

    MCU_Init();

    if(dac_instance == nullptr)
    {
        while(1);
    }

    enableGpioClock(PinMap[pinname].port);

    GPIO_InitTypeDef GPIO_InitStruct{};

    GPIO_InitStruct.Pin  = PinMap[pinname].pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;

    HAL_GPIO_Init(PinMap[pinname].port, &GPIO_InitStruct);

    hdac = getDAC_Handle(dac_instance);

    int index = dac_index(dac_instance);
    if(index < 0)
    {
        while(1);
    }

    if(!dac_initialized[index])    
    {
        enable_dac_clock(dac_instance);

        hdac->Instance = dac_instance;

        if(HAL_DAC_Init(hdac) != HAL_OK)
        {
            while(1);
        }

        dac_initialized[index] = true;
    }

    DAC_ChannelConfTypeDef sConfig{};

    sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
    sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_EXISTENCE;

    if(HAL_DAC_ConfigChannel(hdac, &sConfig, channel) != HAL_OK)
    {
        while(1);
    }

    if (channel == DAC_CHANNEL_1) {
        if (this->DAC_OUTPUTBUFFER_EXISTENCE == DAC_OUTPUTBUFFER_DISABLE) {
            dac_instance->CR |= (1UL << 1);   // 無効(DISABLE)なら、BOOFF1を 1 にする
        } else {
            dac_instance->CR &= ~(1UL << 1);  // 有効(ENABLE)なら、BOOFF1を 0 にクリアする
        }
    } 
    else if (channel == DAC_CHANNEL_2) {
        if (this->DAC_OUTPUTBUFFER_EXISTENCE == DAC_OUTPUTBUFFER_DISABLE) {
            dac_instance->CR |= (1UL << 17);  // 無効(DISABLE)なら、BOOFF2を 1 にする
        } else {
            dac_instance->CR &= ~(1UL << 17); // 有効(ENABLE)なら、BOOFF2を 0 にクリアする
        }
    }

    if(HAL_DAC_Start(hdac, channel) != HAL_OK)
    {
        while(1);
    }

    initialized = true;
}

void AnalogOut::set_buffer_extence(bool buffer)
{
    if(initialized) return;
    
    if(buffer)  DAC_OUTPUTBUFFER_EXISTENCE = DAC_OUTPUTBUFFER_ENABLE;
    else DAC_OUTPUTBUFFER_EXISTENCE = DAC_OUTPUTBUFFER_DISABLE;
}

void AnalogOut::write(float value)
{
    if(value < 0.0f) value = 0.0f;
    if(value > 1.0f) value = 1.0f;

    write_u16(
        static_cast<uint16_t>(
            value * 65535.0f
        )
    );
}

void AnalogOut::write_u16(uint16_t value)
{
    init();

    uint32_t dac_value = value >> 4;

    if(HAL_DAC_SetValue(
            hdac,
            channel,
            DAC_ALIGN_12B_R,
            dac_value
        ) != HAL_OK)
    {
        while(1);
    }
}