// Clock.hpp
#pragma once

#include "core/System.hpp"
#include "core/TIM_Init.hpp"


class Clock {
public:
/**
 * @brief Timerクラスで使う、DWTの初期化
 * 一度しか呼ばれない
 */
    static void init();

/**
 * @brief " Timerの基軸クロック更新 ""
 * 
 * この関数は、System Tick(systick)により1ms割り込みで呼ばれる。
 * 
 * DWTからTimer用クロックを生成するが、DWTは32bit変数のため、すぐにオーバーフロー(約51秒でwrap)する。
 * 
 * wrap回避のため、64bit変数へ積算による変換を行うことで長時間の基軸クロックを生成している。
 */
    static void Update();

/**
 * @brief " クロックの最新値を渡す "
 * 
 * Update()は1ms周期でしか呼ばれず、これにより更新されるTimer用クロックの値の精度は荒い状態である。
 * 
 * 精度を上げるため、DWTから直接、Update()された時の時間までの差分を計測し、
 * 
 * 更新されたクロック値に足し合わせることで正確なクロック値の生成を行っている。
 */
    static uint64_t now();
private:
    static uint64_t timer_accumulated;
    static uint32_t prev;
};



class TIM_Clock {
public:
    static void init();

    static void start();

    static uint32_t get_counter();

    static TIM_HandleTypeDef& handle();

private:
    static TIM_TypeDef* instance;
    static TIM_HandleTypeDef htim;
};
