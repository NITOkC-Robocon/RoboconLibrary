#include <RoboconLibrary.h>

RawSerial pc(USBTX, USBRX);

AnalogIn In(PA_1);
AnalogOut Out(PA_4);

DigitalOut led(LED);

Ticker switcher;

void switch_Out(){
    static bool state = false;
    if(state){
        Out.write(1.0f);
        led.high();
    }else{
        Out.write(0.5f);
        led.low();
    }
    state = !state;
}

int main()
{
    switcher.attach_ms(switch_Out, 1000);
    
    while(1)
    {
        float value = In.read();
        pc.printf("AnalogIn: %.2f\n", value);
    }
}