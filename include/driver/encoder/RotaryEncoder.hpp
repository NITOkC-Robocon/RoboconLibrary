#pragma once

#ifndef RotaryEncoder_H
#define RotaryEncoder_H

#include "core/PinMap.hpp"
#include "driver/interrupt/InterruptIn.hpp"


/**
 * @brief ロータリーエンコーダ用クラス
 *
 * クラス定義： RotaryEncoder encoder(PIN_A, PIN_B);
 * 
 * <オブジェクト生成例>
 * 
 * RotaryEncoder encoder(PA_0, PA_1);
 * 
 * 
 * RotaryEncoder encoder[2] = {
 * 
 * 　　　{PA_0, PA_1}, 
 * 
 * 　　　{PA_2, PA_3}
 * 
 * };
 */
class RotaryEncoder {
        friend void isr(void* obj);
    private:
        InterruptIn _PIN_A;
        InterruptIn _PIN_B;
        int count;
        unsigned char pos;
        
        // count
        void Proccessing(void);
    public:
        RotaryEncoder(PinName PIN_A, PinName PIN_B);
        
        /**
         * @brief カウントをリセットする
         * 
         * <使用例>
         * 
         * encoder.Reset();
         */
        void Reset(void);

        /**
         * @brief カウントを取得する
         * 
         * <使用例>
         * 
         * int count = encoder.Get_Count();
         * 
         * @return int カウント値
         */
        int Get_Count(void);

        /**
         * @brief 円周を取得する
         * 
         * <使用例>
         * 
         * // 直径100、分解能2048のとき
         * 
         * double circumference = encoder.Get_Circumference(100, 2048); 
         * 
         * @param Diameter 直径
         * @param Resolution 分解能
         * @return double 円周
         */
        double Get_Circumference(int Diameter, int Resolution);
};

#endif
