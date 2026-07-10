#include "core/I2C_Init.hpp"


#if defined(STM32F446xx)
//I2Cクロック有効化
void enableI2CClock(I2C_TypeDef* i2c)
{
    if(i2c == I2C1) __HAL_RCC_I2C1_CLK_ENABLE();
    else if(i2c == I2C2) __HAL_RCC_I2C2_CLK_ENABLE();
    else if(i2c == I2C3) __HAL_RCC_I2C3_CLK_ENABLE();
}

void I2C_SetTiming(I2C_HandleTypeDef* Instance, uint32_t frequency_hz)
{
    Instance->Init.ClockSpeed = frequency_hz;
    Instance->Init.DutyCycle = I2C_DUTYCYCLE_2;
}

#endif