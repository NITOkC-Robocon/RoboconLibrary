#include "pwm/PwmOut.hpp"
#include "serial/Serial.hpp"

static TIM_TypeDef* timers[14] =
{
    TIM1,TIM2,TIM3,TIM4,TIM5,
    TIM6,TIM7,
    TIM8,
    TIM9,TIM10,TIM11,
    TIM12,TIM13,TIM14
};

bool PwmOut::channel_used[14][4] = {0};

static int timerIndex(TIM_TypeDef* tim)
{
    for(int i=0;i<14;i++)
    {
        if(timers[i]==tim) return i;
    }

    return -1;
}

PwmOut::PwmOut(PinName pinName) {
    info = &PinMap[pinName];
    port = info->port;
    pin  = info->pin;
}

void PwmOut::class_initialized() {
    if (initialized) return;

    MCU_Init();
        enableGpioClock(port);

    GPIO_InitTypeDef gpio{};
    gpio.Pin = pin;
    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_NOPULL;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;
    gpio.Alternate = info->af[0];

    HAL_GPIO_Init(port,&gpio);

    for(int i=0;i<info->tim_count;i++)
    {
        TIM_TypeDef* candidate = info->tim[i];
        int tidx = timerIndex(candidate);

        int ch = (info->channel[i] >> 2) - 1;

        if(!channel_used[tidx][ch])
        {
            tim = candidate;
            channel = info->channel[i];

            channel_used[tidx][ch] = true;

            enableTimClock(tim);

            break;
        }
    }

    htim.Instance = tim;

    initialized = true;
}

void PwmOut::enableGpioClock(GPIO_TypeDef* port)
{
    if(port==GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
    if(port==GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    if(port==GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
    if(port==GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
}

void PwmOut::enableTimClock(TIM_TypeDef* tim)
{
    if(tim==TIM1) __HAL_RCC_TIM1_CLK_ENABLE();
    if(tim==TIM2) __HAL_RCC_TIM2_CLK_ENABLE();
    if(tim==TIM3) __HAL_RCC_TIM3_CLK_ENABLE();
    if(tim==TIM4) __HAL_RCC_TIM4_CLK_ENABLE();
    if(tim==TIM5) __HAL_RCC_TIM5_CLK_ENABLE();
    if(tim==TIM8) __HAL_RCC_TIM8_CLK_ENABLE();
    if(tim==TIM9) __HAL_RCC_TIM9_CLK_ENABLE();
    if(tim==TIM10) __HAL_RCC_TIM10_CLK_ENABLE();
    if(tim==TIM11) __HAL_RCC_TIM11_CLK_ENABLE();
    if(tim==TIM12) __HAL_RCC_TIM12_CLK_ENABLE();
    if(tim==TIM13) __HAL_RCC_TIM13_CLK_ENABLE();
    if(tim==TIM14) __HAL_RCC_TIM14_CLK_ENABLE();
}

uint32_t PwmOut::getTimerClock(TIM_TypeDef* tim)
{
    uint32_t pclk;
    uint32_t prescaler;

    if(tim==TIM1 || tim==TIM8 || tim==TIM9 || tim==TIM10 || tim==TIM11){
        pclk = HAL_RCC_GetPCLK2Freq();
        prescaler = (RCC->CFGR & RCC_CFGR_PPRE2) >> 13;
    }
    else
    {
        pclk = HAL_RCC_GetPCLK1Freq();
        prescaler = (RCC->CFGR & RCC_CFGR_PPRE1) >> 10;
    }

    if(prescaler < 4) return pclk;
    else return pclk * 2;
}


void PwmOut::period_us(uint32_t us){
    class_initialized();
    period = us;

    uint32_t clk = getTimerClock(tim);

    uint32_t psc = (clk / 1000000) - 1;
    arr = us - 1;

    htim.Init.Prescaler = psc;
    htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim.Init.Period = arr;
    htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;

    HAL_TIM_PWM_Init(&htim);

    if(tim==TIM1 || tim==TIM8)
        __HAL_TIM_MOE_ENABLE(&htim);

    TIM_OC_InitTypeDef oc{};
    oc.OCMode = TIM_OCMODE_PWM1;
    oc.Pulse = 1500;
    oc.OCPolarity = TIM_OCPOLARITY_HIGH;

    HAL_TIM_PWM_ConfigChannel(&htim,&oc,channel);
    HAL_TIM_PWM_Start(&htim,channel);
}

void PwmOut::period_ms(uint32_t ms){
    period_us(ms * 1000);
}

void PwmOut::pulsewidth_ticks(uint32_t ticks){
    class_initialized();
    __HAL_TIM_SET_COMPARE(&htim, channel, ticks);
}

void PwmOut::pulsewidth(float sec){
    pulsewidth_us(sec * 1000000);
}

void PwmOut::pulsewidth_us(uint32_t us){
    class_initialized();
    __HAL_TIM_SET_COMPARE(&htim, channel, us);
}

void PwmOut::write(float duty){
    class_initialized();
    if(duty < 0) duty = 0;
    if(duty > 1) duty = 1;

    if(arr == 0) return;

    uint32_t compare = (uint32_t)(duty * arr);

    __HAL_TIM_SET_COMPARE(&htim, channel, compare);
}


//=============================
//======== Servoクラス ========
//=============================

Servo::Servo(PinName pin) : pwm(pin)
{
    pwm.period_us(20000);
}

void Servo::period_us(uint32_t us)
{
    if(us < 5000) us = 5000;
    if(us > 30000) us =30000;
    pwm.period_us(us);
}

void Servo::period_ms(uint32_t ms)
{
    pwm.period_us(ms * 1000);
}

void Servo::setPulseRange(uint32_t min, uint32_t max)
{
    min_us = min;
    max_us = max;
}

void Servo::pulsewidth_us(uint32_t us)
{
    if(us < min_us) us = min_us;
    if(us > max_us) us = max_us;

    pwm.pulsewidth_us(us);
}