#pragma once

#include "core/System.hpp"
#include "TIM_Events.hpp"
#include "TIM_EventScheduler.hpp"

/**
 * @brief 時間指定コールバック用クラス
 * 
 * 機能説明：
 * 指定時間後、設定した関数を実行することができる
 * 
 * <オブジェクト生成例>
 * Timeout timeout;
 */
class Timeout : public TIM_Event {
public:
    using Callback = void(*)();

    Timeout() = default;

    /**
     * @brief 指定したミリ秒後に関数を実行するように設定する
     * 
     * <使用例>
     * timeout.attach_ms(my_callback, 1000);
     * 
     * @param cb 実行したい関数ポインタ
     * @param period_ms 実行までの時間(ミリ秒)
     */
    void attach_ms(Callback cb, uint32_t period_ms);

    /**
     * @brief 指定したマイクロ秒後に関数を実行するように設定する
     * 
     * <使用例>
     * timeout.attach_us(my_callback, 500);
     * 
     * @param cb 実行したい関数ポインタ
     * @param period_us 実行までの時間(マイクロ秒)
     */
    void attach_us(Callback cb, uint32_t period_us);

    /**
     * @brief 設定したタイマーを再開する
     * 
     * <使用例>
     * timeout.active();
     */
    void active();

    /**
     * @brief 現在のタイマーを停止する
     * @note タイマーのカウントはリセットされる
     * 
     * <使用例>
     * timeout.detach();
     */
    void detach();

    /**
     * @brief タイムアウト発生時に呼ばれる内部処理
     */
    void fire() override;
private:
    Callback callback = nullptr;
    uint32_t period = 0;
};