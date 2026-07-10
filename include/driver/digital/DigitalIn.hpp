#pragma once

#include "core/PinMap.hpp"

/**
 * @brief デジタル入力用クラス
 * 
 * ピンのプル状態はデフォルトでPullNoneに設定されます。
 * 
 * 必要に応じてPullUpまたはPullDownを指定してください。
 *
 * <オブジェクト生成例>
 * 
 * DigitalIn button(PA_0);
 * 
 * DigitalIn buttons[2] = {PA_0, PA_1};
 * 
 * DigitalIn button(PA_0, PullUp);
 * 
 * DigitalIn button[2] = {{PA_0, PullUp}, {PA_1, PullDown}};
 */
class DigitalIn{
private:
    GPIO_TypeDef* port;
    uint16_t      pin;
    uint32_t pin_pull;

    mutable bool initialized = false;
    void class_initialized() const;

public:
    DigitalIn(PinName pinName, PinMode pull = PullNone);

    /**
     * @brief デジタル入力値を取得する
     * 
     * <使用例>

     * uint8_t value = button.read();
     * 
     * @return デジタル入力値 (0 or 1)
     */
    uint8_t read() const;

    /**
     * @brief ピンのプル状態を設定する
     * 
     * <使用例>
     * 
     * button.mode(PullUp);
     * 
     * @param mode ピンのプル状態 (PullNone, PullUp, PullDown)
     */
    void mode(PinMode mode);

    /**
     * @brief デジタル入力値を取得するための型変換演算子
     * 
     * <使用例>
     * 
     * uint8_t value = button; // button.read()と同じ
     * 
     * @return デジタル入力値 (0 or 1)
     */
    operator int() const {
        return read();
    }
};
