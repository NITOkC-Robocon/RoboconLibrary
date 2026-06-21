#include "driver/timer/Clock.hpp"

void Clock::init() {
    static bool initialized = false;
    if (initialized) return;
    
    MCU_Init();
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;

    prev = DWT->CYCCNT;

    initialized = true;
}

uint64_t Clock::timer_accumulated = 0;
uint32_t Clock::prev = 0;

void Clock::Update() {
    uint32_t now = DWT->CYCCNT;

    uint32_t dt = now - prev;
    prev = now;
    timer_accumulated += dt;
}

uint64_t Clock::now()
{
    uint32_t primask = __get_PRIMASK();
    __disable_irq();

    uint32_t now = DWT->CYCCNT;
    uint64_t t = timer_accumulated + (uint32_t)(now - prev);

    __set_PRIMASK(primask);
    return t;
}


//割り込み用TIMクロック

TIM_TypeDef* TIM_Clock::instance = nullptr;
TIM_HandleTypeDef TIM_Clock::htim{};

TIM_HandleTypeDef& TIM_Clock::handle(){
    return htim;
}

void TIM_Clock::init()
{
    static bool initialized = false;
    if (initialized) return;

    MCU_Init();

    instance = TIM_instance;

    enableTimClock(instance);

    uint32_t prescaler = (getTimerClock(instance) / 1000000) - 1;

    htim.Instance = instance;

    htim.Init.Prescaler = (uint16_t)prescaler;
    htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim.Init.Period = getTIMMaxCount(instance);
    htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    HAL_TIM_OC_Init(&htim);

    TIM_OC_InitTypeDef sConfig = {};
    sConfig.OCMode = TIM_OCMODE_TIMING;
    sConfig.Pulse = 0;

    HAL_TIM_OC_ConfigChannel(&htim, &sConfig, TIM_CHANNEL_1);

    HAL_NVIC_SetPriority(getTIMUpdateIRQn(instance), 1, 0);
    HAL_NVIC_EnableIRQ(getTIMUpdateIRQn(instance));

    initialized = true;
}

void TIM_Clock::start()
{
    init();
    HAL_TIM_Base_Start(&htim);
    HAL_TIM_OC_Start(&htim, TIM_CHANNEL_1);

    __HAL_TIM_ENABLE_IT(&htim, TIM_IT_UPDATE);
}


uint32_t TIM_Clock::overflow_count = 0;
uint32_t TIM_Clock::get_counter()
{
    if(getTIMMaxCount(instance) == UINT32_MAX)
    {
        return __HAL_TIM_GET_COUNTER(&htim);
    }

    uint32_t high1;
    uint32_t high2;
    uint16_t low;

    do
    {
        high1 = overflow_count;
        low   = __HAL_TIM_GET_COUNTER(&htim);
        high2 = overflow_count;
    }
    while(high1 != high2);

    return (high1 << 16) | low;
}