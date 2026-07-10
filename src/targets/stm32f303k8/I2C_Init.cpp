#include "core/I2C_Init.hpp"


#if defined(STM32F303x8)

uint32_t getI2CClockFreq(I2C_TypeDef* i2c);

//I2Cクロック有効化
void enableI2CClock(I2C_TypeDef* i2c)
{
    if(i2c == I2C1) __HAL_RCC_I2C1_CLK_ENABLE();
}

//I2Cクロック周波数取得
uint32_t getI2CClockFreq(I2C_TypeDef* i2c)
{
    uint32_t i2c_clock;
    uint32_t cfgr3 = RCC->CFGR3;

    if (cfgr3 & RCC_CFGR3_I2C1SW) {
        i2c_clock = HAL_RCC_GetSysClockFreq();
    } else {
        i2c_clock = HSI_VALUE;    // 通常8000000
    }

    return i2c_clock;
}

void I2C_SetTiming(I2C_HandleTypeDef* Instance, uint32_t frequency_hz)
{
    if(getI2CClockFreq(Instance->Instance) == 8000000) // 8 MHz
    {
        if(frequency_hz == 100000) // 100 kHz
            Instance->Init.Timing = 0x00201D2B;
        else if(frequency_hz == 400000) // 400 kHz
            Instance->Init.Timing = 0x0010020A;
        else if(frequency_hz == 1000000) // 1 MHz
            Instance->Init.Timing = 0x00100001;
    }
    else if(getI2CClockFreq(Instance->Instance) == 36000000) // 36 MHz
    {
        if(frequency_hz == 100000) // 100 kHz
            Instance->Init.Timing = 0x00C08CCB;
        else if(frequency_hz == 400000) // 400 kHz
            Instance->Init.Timing = 0x00701138;
        else if(frequency_hz == 1000000) // 1 MHz
            Instance->Init.Timing = 0x0050050E;
    }
    else if(getI2CClockFreq(Instance->Instance) == 72000000) // 72 MHz
    {
        if(frequency_hz == 100000) // 100 kHz
            Instance->Init.Timing = 0x00C08CCB;
        else if(frequency_hz == 400000) // 400 kHz
            Instance->Init.Timing = 0x00701138;
        else if(frequency_hz == 1000000) // 1 MHz
            Instance->Init.Timing = 0x0050050E;
    }
    else
    {
        // エラー（ここ重要）
        while (1);
    }
}

#endif