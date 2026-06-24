#include <RoboconLibrary.h>

AnalogIn In(PA_1);
AnalogOut Out(PA_4);

void AnalogCom()
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