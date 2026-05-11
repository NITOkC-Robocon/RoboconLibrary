#include <RoboconLibrary.h>

PwmOut pwm(PC_9);
DigitalOut dir(PB_8);

int main(void) {
    pwm.period_us(1500);

    while(1){
        pwm.write(0.2);
        dir = 1;
        HAL_Delay(1000);

        pwm.write(0.6);
        dir = 0;
        HAL_Delay(1000);
    }
}
