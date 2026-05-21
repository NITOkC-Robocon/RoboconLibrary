#pragma once

#include "core/System.hpp"
#include "driver/timer/Clock.hpp"
#include <cstdint>


class Timer {
private:
    uint64_t start_time;
    uint64_t accumulated;
    bool running;

    mutable bool initialized = false;
    void class_initialized() const;

public:
    Timer();

/**
 * @brief " タイマー 計測開始 "
 */
    void start();

/**
 * @brief " タイマー 計測停止 "
 */
    void stop();

/**
 * @brief "タイマー リセット "
 */
    void reset();

    uint64_t read() const;
/**
 * @brief " 経過時間の取得(マイクロ秒) "
 * 
 * 短時間用途専用（PID制御など）
 * 
 * 約71分でオーバーフローする（uint32_t制限）
 * @return 経過時間 [us]
 */
    uint32_t read_us() const;

/**
 * @brief " 経過時間の取得(ミリ秒) "
 * @return 経過時間 [ms] 
*/
    uint32_t read_ms() const;

/**
 * @brief " 計測中か否かを判定 ""
 * @return true　もしくは　false
 */
    bool isRunning() const;
};