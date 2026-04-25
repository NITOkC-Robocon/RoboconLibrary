#include "encoder/RotaryEncoder.hpp"

static void isr(void* obj){
    static_cast<RotaryEncoder*>(obj)->Proccessing();
} 

RotaryEncoder::RotaryEncoder(PinName PIN_A, PinName PIN_B) : _PIN_A(PIN_A), _PIN_B(PIN_B) {
    count = 0;
    pos = 0;

    _PIN_A.mode(PullUp);
    _PIN_A.rise(this, isr);
    _PIN_A.fall(this, isr);
    
    _PIN_B.mode(PullUp);
    _PIN_B.rise(this, isr);
    _PIN_B.fall(this, isr);
}

// Processing part of encoder
void RotaryEncoder::Proccessing() {
    unsigned char D = (!(_PIN_B.read()) << 1) + (!(_PIN_A.read()));
    unsigned char old_data = pos & 3;
    unsigned char new_data = (pos & 48) >> 4;
    
    if (D == 3){
        D = 2;
    }
    else if (D == 2){
        D = 3;
    }
    
    if (D != old_data){
        if (new_data == 0){
            if (D == 1 || D == 3){
                new_data = D;
            }
        }
        else {
            if (D == 0){
                if (new_data == 1 && old_data == 3){
                    count++;
                }
                else if (new_data == 3 && old_data == 1){
                    count--;
                }
                new_data = 0;
            }
        }
        pos = (new_data << 4) + (old_data << 2) + D;
    }
}

// Reset encoder counts
void RotaryEncoder::Reset() {
    count = 0;
}

// Display of encoder counts
int RotaryEncoder::Get_Count() {
    return (count);
}

// Circumference display
double RotaryEncoder::Get_Circumference(int Diameter, int Resolution) {
    return (Diameter * 3.14 * ((double)count / Resolution));
}
