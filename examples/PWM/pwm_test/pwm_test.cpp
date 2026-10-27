#include <RoboconLibrary.h>

PwmOut pwm(PC_9);   //J1
DigitalOut dir(PB_8);   //J1

int main(void) {
    pwm.period_us(1500);    //周期設定

    while(1){
        pwm.write(0.2);
        dir = 1;
        HAL_Delay(1000);

        pwm.write(0.6);
        dir = 0;
        HAL_Delay(1000);
    }
}
