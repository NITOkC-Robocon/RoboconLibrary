#pragma once

#include "core/PinMap.hpp"


/**
 * @brief デジタル出力用クラス
 * 
 * <オブジェクト生成例>
 * 
 * DigitalOut led(PA_0);
 * 
 * DigitalOut led[2] = {PA_0, PA_1};
 */
class DigitalOut
{
private:
    GPIO_TypeDef* port;
    uint16_t      pin;

    mutable bool initialized = false;
    void class_initialized() const; 

public:
    DigitalOut(PinName pinName);

    /**
     * @brief デジタル出力値を設定する
     * 
     * <使用例>
     *
     * led.write(1);　　// HIGH
     * 
     * led.write(0);　　// LOW
     *
     * @param value 0または1のデジタル出力値
     */
    void write(uint8_t value);

    /**
     * @brief デジタル出力値を取得する
     * 
     * <使用例>
     *
     * int value = led.read();
     *
     * @return 0または1のデジタル出力値
     */
    int read() const;

    /**
     * @brief デジタル出力値を反転する
     * 
     * <使用例>
     *
     * led.toggle(); 　// HIGH -> LOW または LOW -> HIGH
     */
    void toggle();

    /**
     * @brief デジタル出力値をHIGHに設定する
     * 
     * <使用例>
     *
     * led.high();
     */
    void high();

    /**
     * @brief デジタル出力値をLOWに設定する
     * 
     * <使用例>
     * 
     * led.low();
     */
    void low();

    /**
     * @brief デジタル出力値を設定する演算子オーバーロード
     * 
     * <使用例>
     *
     * led = 1; 　　// HIGH
     * 
     * led = 0; 　　// LOW
     *
     * @param value 0または1のデジタル出力値
     * @return 自身のインスタンスへの参照
     */
    DigitalOut& operator = (int value){
        write(value);
        return *this;
    }

    /**
     * @brief デジタル出力値を取得する演算子オーバーロード
     * 
     * <使用例>
     *
     * int value = led; // 0または1のデジタル出力値
     *
     * @return 0または1のデジタル出力値
     */
    operator int() const {
        return read();
    }
};
