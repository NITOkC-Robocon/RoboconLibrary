#include "digital/DigitalIn.hpp"

DigitalIn::DigitalIn(PinName pinName, uint32_t pull){
    MCU_Init();

    port = PinMap[pinName].port;
    pin  = PinMap[pinName].pin;

    enableClock(port);

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin  = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = pull;

    HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void DigitalIn::enableClock(GPIO_TypeDef* port_GPIO)
{
    if(port_GPIO == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
    if(port_GPIO == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    if(port_GPIO == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
    if(port_GPIO == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
}

//機能メソッド
uint8_t DigitalIn::read(){
    return (uint8_t)HAL_GPIO_ReadPin(port, pin);
}

void DigitalIn::mode(PinMode mode){
    uint32_t pull;

    switch(mode){
        case PullUp:
            pull = GPIO_PULLUP;
            break;
        case PullDown:
            pull = GPIO_PULLDOWN;
            break;
        default:
            pull = GPIO_NOPULL;
            break;       
    }

    GPIO_InitTypeDef GPIO_InitStruct = {0};

    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = pull;

    HAL_GPIO_Init(port, &GPIO_InitStruct);
}