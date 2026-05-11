#include "driver/interrupt/InterruptIn.hpp"

// staticメンバ初期化
InterruptIn* InterruptIn::instances[16] = {0};

//ピン番号取得
static int get_pin_number(uint16_t pin) {
    return __builtin_ctz(pin);
}

//======================================
// IRQ共通ハンドラ
extern "C" void EXTI0_IRQHandler(void){
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
}

extern "C" void EXTI1_IRQHandler(void){
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
}

extern "C" void EXTI2_IRQHandler(void){
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);
}

extern "C" void EXTI3_IRQHandler(void){
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}

extern "C" void EXTI4_IRQHandler(void){
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

extern "C" void EXTI9_5_IRQHandler(void){
    for(int i = 5; i <= 9; i++){
        HAL_GPIO_EXTI_IRQHandler(1 << i);     
    }
}

extern "C" void EXTI15_10_IRQHandler(void){
    for(int i = 10; i <= 15; i++){
        HAL_GPIO_EXTI_IRQHandler(1 << i);     
    }
}

// IRQ共通ハンドラ(関数呼び出し)
extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    int pin_number = __builtin_ctz(GPIO_Pin);

    if (InterruptIn::instances[pin_number]) {
        InterruptIn::instances[pin_number]->handle_interrupt();
    }
}
//============================================================

//コンストラクタ
InterruptIn::InterruptIn(PinName pinName, PinMode pull) {
    port = PinMap[pinName].port;
    pin = PinMap[pinName].pin;
    pin_number = get_pin_number(PinMap[pinName].pin);

     pull_mode = PinPull[pull];

    rise_func = nullptr;
    rise_obj = nullptr;
    fall_func = nullptr;
    fall_obj = nullptr;

    instances[pin_number] = this;
}

void InterruptIn::class_initialized() {
    if (initialized) return;

    MCU_Init();
    init_exti();
    
    initialized = true;
}

// EXTI初期化
void InterruptIn::init_exti() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // GPIOクロック有効化
    if (port == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
    if (port == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    if (port == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
    if (port == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();

    // GPIO設定
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIO_InitStruct.Pull = pull_mode;

    HAL_GPIO_Init(port, &GPIO_InitStruct);

    // NVIC設定
    IRQn_Type irq = getExtiIRQ(pin_number);

    HAL_NVIC_SetPriority(irq, 5, 0);
    HAL_NVIC_EnableIRQ(irq);
}

//mode設定
void InterruptIn::mode(PinMode mode){
    pull_mode = PinPull[mode];

    if (initialized) {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        GPIO_InitStruct.Pin  = pin;
        GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
        GPIO_InitStruct.Pull = pull_mode;

        HAL_GPIO_Init(port, &GPIO_InitStruct);
    }
}

// 関数登録(rise時)
void InterruptIn::rise(void* obj, void (*func)(void*)) {
    class_initialized();

    rise_obj = obj;
    rise_func = func;
}

// 関数登録(fall時)
void InterruptIn::fall(void* obj, void (*func)(void*)) {
    class_initialized();

    fall_obj = obj;
    fall_func = func;
}

// 
int InterruptIn::read() {
    class_initialized();
    return HAL_GPIO_ReadPin(port, pin) == GPIO_PIN_SET;
}

// 割り込み処理
void InterruptIn::handle_interrupt() {
    class_initialized();

    GPIO_PinState state = HAL_GPIO_ReadPin(port, pin);

    if (state == GPIO_PIN_SET) {
        if (rise_func) rise_func(rise_obj);
    } else {
        if (fall_func) fall_func(fall_obj);
    }
}