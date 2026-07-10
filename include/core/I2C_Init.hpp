#pragma once

#if defined(STM32F446xx)
extern "C" {
    #include "stm32f4xx_hal.h"
}
constexpr uint32_t GPIO_SPEED_FREQ = GPIO_SPEED_FREQ_VERY_HIGH;

#elif defined(STM32F303x8)
extern "C" {
    #include "stm32f3xx_hal.h"
}
constexpr uint32_t GPIO_SPEED_FREQ = GPIO_SPEED_FREQ_HIGH;

uint32_t getI2CClockFreq(I2C_TypeDef* i2c);
#endif

void enableI2CClock(I2C_TypeDef* i2c);
void I2C_SetTiming(I2C_HandleTypeDef* Instance, uint32_t frequency_hz);