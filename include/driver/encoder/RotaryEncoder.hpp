#pragma once

#ifndef RotaryEncoder_H
#define RotaryEncoder_H

#include "core/PinMap.hpp"
#include "driver/interrupt/InterruptIn.hpp"


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
        
        // Set the count value to 0 
        void Reset(void);
        // return a count
        int Get_Count(void);
        // return the circumference
        double Get_Circumference(int Diameter, int Resolution);
};

#endif
