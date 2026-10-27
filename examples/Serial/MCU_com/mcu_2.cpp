#include <RoboconLibrary.h>

RawSerial mcu1(PC_10, PC_11);

//割り込み関数(受け取った値を加工してマイコン１に返す)
void return_data(){
    char c = mcu1.getc();
    mcu1.putc(c + 1);
}

int main(){
    //割り込み関数登録
    mcu1.attach(&return_data, RawSerial::RxIrq);

    while(1){}
}