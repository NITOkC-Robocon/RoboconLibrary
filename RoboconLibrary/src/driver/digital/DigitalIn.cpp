#include "driver/digital/DigitalIn.hpp"

DigitalIn::DigitalIn(PinName pinName, PinMode pull){
    port = PinMap[pinName].port;
    pin  = PinMap[pinName].pin;
    pin_pull = PinPull[pull];
}

void DigitalIn::class_initialized() const {
    if (initialized) return;
    
    MCU_Init();
    enableClock(port);

    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin  = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = pin_pull;

    HAL_GPIO_Init(port, &GPIO_InitStruct);

    initialized = true;
    
}

void DigitalIn::enableClock(GPIO_TypeDef* port_GPIO) const {
    if(port_GPIO == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
    if(port_GPIO == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    if(port_GPIO == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
    if(port_GPIO == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
}

uint8_t DigitalIn::read() const {
    class_initialized();
    return HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET;
}

void DigitalIn::mode(PinMode mode) {
    class_initialized();
    uint32_t pin_pull = PinPull[mode];

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = pin_pull;

    HAL_GPIO_Init(port, &GPIO_InitStruct);
}