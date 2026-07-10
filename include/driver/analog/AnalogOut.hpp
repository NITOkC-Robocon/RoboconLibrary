#pragma once

#include "core/PinMap.hpp"
#include "core/ADC_DAC_Init.hpp"

/**
 * @brief アナログ出力(DAC)用クラス
 *
 * アナログ出力信号を生成するために使用します。
 *
 * <オブジェクト生成例>
 * 
 * AnalogOut actuator(PA_0);
 * 
 * AnalogOut actuators[2] = {PA_0, PA_4};
 */
class AnalogOut {
private:
    PinName pinname;

    DAC_HandleTypeDef* hdac = nullptr;
    DAC_TypeDef* dac_instance = nullptr;
    uint32_t channel = 0;

    uint32_t DAC_OUTPUTBUFFER_EXISTENCE;

    bool initialized = false;
    void init();

public:
    AnalogOut(PinName pin);

/**
 * @brief バッファの有無を設定する
 * （mainの初めに呼び出す必要あり）
 * 
 * <使用例>
 * 
 * actuator.set_buffer_extence(true); // バッファ有効
 *
 * @param buffer バッファの有無 (true: 有効, false: 無効)
 */
    void set_buffer_extence(bool buffer = DefaultBufferExistence);

/**
 * @brief アナログ出力値を浮動小数点で設定する
 * 
 * <使用例>
 * 
 * actuator.write(0.5f); // 0.5Vを出力
 * 
 * @param value 0.0〜1.0の範囲のアナログ出力値
 */
    void write(float value);

/**
 * @brief アナログ出力値を16bitで設定する
 * 
 * <使用例>
 * 
 * actuator.write_u16(32768); // 0.5Vを出力
 * 
 * @param value 0〜65535の範囲の16bitアナログ出力値
 */
    void write_u16(uint16_t value);
};
