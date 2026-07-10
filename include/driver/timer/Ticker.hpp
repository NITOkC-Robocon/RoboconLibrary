#pragma once

#include "core/System.hpp"
#include "TIM_Events.hpp"
#include "TIM_EventScheduler.hpp"

/**
 * @brief 周期的コールバック実行用クラス
 * 
 * 機能説明：
 * 一定周期で、設定した関数を自動で呼び出すことができる
 * 
 * <オブジェクト生成例>
 * 
 * Ticker ticker;
 */
class Ticker : public TIM_Event {
public:
    using Callback = void(*)();

    Ticker() = default;

    /**
     * @brief コールバック関数及び、実行周期の設定
     * 
     * <使用例>
     * 
     * void led_toggle();　　//Lチカ用関数を宣言
     * 
     * ticker.attach_ms(led_toggle, 100)　　//Lチカ用関数を100ms周期で設定
     * 
     * @param cb コールバック関数
     * @param period_ms 周期（ミリ秒）
     */
    void attach_ms(Callback cb, uint32_t period_ms);

    /**
     * @brief コールバック関数及び、実行周期の設定
     * 
     * <使用例>
     * 
     * void led_toggle();　　//Lチカ用関数を宣言
     * 
     * ticker.attach_us(led_toggle, 100)　　//Lチカ用関数を100us周期で設定
     * 
     * @param cb コールバック関数
     * @param period_us 周期（マイクロ秒）
     */
    void attach_us(Callback cb, uint32_t period_us);

    /**
     * @brief 停止したコールバックを再アクティブ化
     * @note 最後に行ったattach()の設定をもとにアクティブ化する
     * 
     * <使用例>
     * 
     * ticker.active();
     */
    void active();

    /**
     * @brief アクティブ状態のコールバックを停止
     * @note 最後に行ったattach()の設定はリセットされない
     * 
     * <使用例>
     * 
     * ticker.detach();
     */
    void detach();

    void fire() override;

private:
    Callback callback = nullptr;
    uint32_t period = 0;
};