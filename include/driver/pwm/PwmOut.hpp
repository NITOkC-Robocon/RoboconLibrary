#pragma once

#include "core/PinMap.hpp"
#include "core/TIM_Manager.hpp"

 /**
  * @brief pwm出力用クラス
  * 
  * <オブジェクト生成例>
  * 
  * PwmOut pwm(PA_0);
  * 
  * PwmOut pwm[2] = {PA_0, PA_1};
  */
class PwmOut
{
private:
    const PinInfo* info;

    GPIO_TypeDef* port;
    uint16_t pin;

    TIM_TypeDef* tim = nullptr;
    uint32_t channel = 0;

    uint32_t period = 0;

    uint32_t arr = 0;

    static bool channel_used[TIMER_COUNT][4];

    mutable bool initialized = false;
    void class_initialized();

public:
    PwmOut(PinName pinName);

    TIM_HandleTypeDef htim;

    /**
     * @brief PWMの周期を設定する
     * 
     * <使用例>
     * 
     * pwm.period_ms(20); // 20msに設定
     * 
     * @param us 設定する周期(マイクロ秒)
     */
    void period_us(uint32_t us);

    /**
     * @brief PWMの周期を設定する
     * 
     * <使用例>
     * 
     * pwm.period_ms(20); // 20msに設定
     * 
     * @param ms 設定する周期(ミリ秒)
     */
    void period_ms(uint32_t ms);

    /**
     * @brief PWMのパルス幅を設定する
     * 
     * <使用例>
     * 
     * pwm.pulsewidth_ticks(1500); // 1500ticksに設定
     * 
     * @param ticks 設定するパルス幅(ticks)
     */
    void pulsewidth_ticks(uint32_t ticks);

    /**
     * @brief PWMのパルス幅を設定する
     * 
     * <使用例>
     * 
     * pwm.pulsewidth_ms(1500); // 1500ミリ秒に設定
     * 
     * @param ms 設定するパルス幅(ミリ秒)
     */
    void pulsewidth_ms(float ms);

    /**
     * @brief PWMのパルス幅を設定する
     * 
     * <使用例>
     * 
     * pwm.pulsewidth_us(1500); // 1500マイクロ秒に設定
     * 
     * @param us 設定するパルス幅(マイクロ秒)
     */
    void pulsewidth_us(uint32_t us);

    /**
     * @brief PWMのデューティ比を設定する
     * 
     * <使用例>
     * 
     * pwm.write(0.5); // デューティ比50%に設定
     * 
     * @param duty デューティ比(0.0~1.0)
     */
    void write(float duty);
};

/**
 * @brief サーボモーターを制御するクラス
 * @note オブジェクト生成時、周期はデフォルトで20ms、パルス幅は500us~2500usに設定されます。
 * 
 * <オブジェクト生成例>
 * 
 * Servo servo(PA_0);
 */
class Servo 
{
private:
    PwmOut pwm;

public:
    Servo(PinName pin);

    uint32_t min_us = 500;
    uint32_t max_us = 2500;

    /**
     * @brief サーボのpwmの周期を設定する
     * 
     * <使用例>
     * 
     * servo.period_us(20000); // 20000マイクロ秒に設定
     * 
     * @param us 設定する周期(マイクロ秒)
     */
    void period_us(uint32_t us);

    /**
     * @brief サーボのpwmの周期を設定する
     * 
     * <使用例>
     * 
     * servo.period_ms(20); // 20ミリ秒に設定
     * 
     * @param ms 設定する周期(ミリ秒)
     */
    void period_ms(uint32_t ms);

    /**
     * @brief 有効なパルス幅の範囲をミリ秒単位で設定する
     * 
     * <使用例>
     * 
     * servo.setPulseRange(1000, 2000); // 1000ms~2000msに設定
     * 
     * @param min 設定する最小パルス幅(ミリ秒)
     * @param max 設定する最大パルス幅(ミリ秒）
     */
    void setPulseRange(uint32_t min, uint32_t max);

    /**
     * @brief パルス幅を設定する
     * 
     * <使用例>
     * 
     * servo.pulsewidth_us(1500); // 1500マイクロ秒に設定
     * 
     * @param us 設定するパルス幅(マイクロ秒)
     */
    void pulsewidth_us(uint32_t us);
};