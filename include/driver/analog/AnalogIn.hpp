#pragma once

#include "core/PinMap.hpp"
#include "core/ADC_DAC_Init.hpp"


/**
 * @brief アナログ入力(ADC)用クラス
 *
 * <オブジェクト生成例>
 * AnalogIn sensor(PA_0);
 *
 * AnalogIn sensors[2] = {PA_0, PA_1};
 */
class AnalogIn {
private:
    PinName pinname;

    ADC_HandleTypeDef* hadc = nullptr;
    ADC_TypeDef* adc_instance = nullptr;
    uint32_t channel = 0;

    bool initialized = false;
    void init();

public:
    AnalogIn(PinName pin);

/**
 * @brief アナログ入力値を16bitで取得する
 * 
 * <使用例>
 *
 * uint16_t value = sensor.read_u16();
 *
 * @return 16bitのアナログ入力値(0~65535)
 */
    uint16_t read_u16();

/**
 * @brief アナログ入力値を浮動小数点で取得する
 * 
 * <使用例>
 *
 * float value = sensor.read();
 *
 * @return 0.0〜1.0の範囲のアナログ入力値
 */
    float read();
};