#include <RoboconLibrary.h>

DigitalOut led(PA_5);

int main(){
    while(1){
        led = !led;
        HAL_Delay(100);
    }
    
    return 0;
}