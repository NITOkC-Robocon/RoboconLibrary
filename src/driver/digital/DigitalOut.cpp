#include "driver/digital/DigitalOut.hpp"

#include "core/System.hpp"

DigitalOut::DigitalOut(PinName pinName){
    port = PinMap[pinName].port;
    pin = PinMap[pinName].pin;
}

void DigitalOut::class_initialized() const{
    if(initialized) return;

    MCU_Init();
    enableGpioClock(port);

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin   = pin;
    GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull  = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(port, &GPIO_InitStruct);

    initialized = true;
};


//機能メソッド
void DigitalOut::write(uint8_t value){
    class_initialized();
    HAL_GPIO_WritePin(port, pin, (GPIO_PinState)value);
}

int DigitalOut::read() const{
    class_initialized();
    return HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET;
}

void DigitalOut::toggle(){
    class_initialized();
    HAL_GPIO_TogglePin(port, pin);
}

void DigitalOut::high() {
    class_initialized();
    write(1);
}

void DigitalOut::low() {
    class_initialized();
    write(0);
}