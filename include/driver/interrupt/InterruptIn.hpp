#pragma once

#include "core/PinMap.hpp"


#ifndef INTERRUPTIN_H
#define INTERRUPTIN_H

/**
 * @brief ピンの立ち上がり/立ち下がりを検出するクラス
 * 
 * 機能説明：
 * 
 * 外部入力の変化を検出して、登録した関数を呼び出します。
 * 
 * ボタン入力やセンサの状態変化を扱うときに便利です。
 * @note オブジェクト生成時、プル状態はPullNoneに設定されている
 * 
 * <オブジェクト生成例>
 * 
 * InterruptIn button(PB_0, PullUp);
 * @param pinName 対象のピン
 * @param pull プルアップ/プルダウンの設定
 */
class InterruptIn {
    friend void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
private:
    static InterruptIn* instances[16];

    GPIO_TypeDef* port;
    uint16_t pin;
    uint32_t pull_mode;
    int pin_number;

    mutable bool initialized = false;
    void class_initialized();
    void init_exti();

    void (*rise_func)(void*);
    void* rise_obj;
    void (*fall_func)(void*);
    void* fall_obj;

    void handle_interrupt();
public:
    InterruptIn(PinName pinName, PinMode pull = PullNone);

    /**
     * @brief ピンのプルアップ/プルダウン状態を変更する
     * 
     * <使用例>
     * button.mode(PullUp);
     * 
     * @param mode 設定したいプル状態（PullNone/PullUp/PullDown）
     */
    void mode(PinMode mode);

    /**
     * @brief 立ち上がりエッジで呼び出す関数を登録する
     * 
     * <使用例>
     * button.rise(nullptr, my_callback);
     * 
     * @param obj コールバック関数内で使うオブジェクトポインタ
     * @param func 実行したい関数ポインタ
     */
    void rise(void* obj, void (*func)(void*));

    /**
     * @brief 立ち下がりエッジで呼び出す関数を登録する
     * 
     * <使用例>
     * button.fall(nullptr, my_callback);
     * 
     * @param obj コールバック関数内で使うオブジェクトポインタ
     * @param func 実行したい関数ポインタ
     */
    void fall(void* obj, void (*func)(void*));

    /**
     * @brief 現在のピン状態を取得する
     * 
     * <使用例>
     * int state = button.read();
     * 
     * @return 1ならHIGH、0ならLOW
     */
    int read();
};

#endif