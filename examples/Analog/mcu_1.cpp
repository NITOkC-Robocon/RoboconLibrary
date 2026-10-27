#include <RoboconLibrary.h>

RawSerial pc(USBTX, USBRX);

AnalogIn In(PA_1);  //アナログ入力用ピン
AnalogOut Out(PA_4);    //アナログ出力用ピン

DigitalOut led(LED);    //入出力確認用LED

Ticker switcher;    //出力切り替えトリガー用

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
    switcher.attach_ms(switch_Out, 1000);   //一秒ごとに出力を切り替えるためのTicker
    
    while(1)
    {
        float value = In.read();
        pc.printf("AnalogIn: %.2f\n", value);
    }
}