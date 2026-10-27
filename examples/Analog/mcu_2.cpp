#include <RoboconLibrary.h>

AnalogIn In(PA_1);  //アナログ入力用
AnalogOut Out(PA_4);    //アナログ出力用

void AnalogCom()    //出力を1/2にして返すだけの関数
{
    float value = In.read();
    Out.write(value/2);
}

int main()
{
    while(1)
    {
        AnalogCom();
    }
}