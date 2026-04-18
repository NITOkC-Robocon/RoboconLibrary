#include "digital/DigitalOut.hpp"

DigitalOut::DigitalOut(PinName pinName){
    MCU_Init();

    port = PinMap[pinName].port;
    pin = PinMap[pinName].pin;

    enableClock(port);

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin   = pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void DigitalOut::enableClock(GPIO_TypeDef* port_GPIO){
    if(port_GPIO == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
    if(port_GPIO == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    if(port_GPIO == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
    if(port_GPIO == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
}

//機能メソッド
void DigitalOut::write(uint8_t value){
    HAL_GPIO_WritePin(port, pin, (GPIO_PinState)value);
}

int DigitalOut::read(){
    return HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET;
}

void DigitalOut::toggle(){
    HAL_GPIO_TogglePin(port, pin);
}

void DigitalOut::high() { write(1); }

void DigitalOut::low() { write(0); }