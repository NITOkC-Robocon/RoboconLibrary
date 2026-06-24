#include "driver/digital/DigitalIn.hpp"

#include "core/System.hpp"

DigitalIn::DigitalIn(PinName pinName, PinMode pull){
    port = PinMap[pinName].port;
    pin  = PinMap[pinName].pin;
    pin_pull = PinPull[pull];
}

void DigitalIn::class_initialized() const {
    if (initialized) return;
    
    MCU_Init();
    enableGpioClock(port);

    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Pin  = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = pin_pull;

    HAL_GPIO_Init(port, &GPIO_InitStruct);

    initialized = true;
    
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