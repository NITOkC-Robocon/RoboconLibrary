#include <RoboconLibrary.h>

RawSerial pc(USBTX, USBRX);
RawSerial mcu2(PC_10, PC_11);

//割り込み関数(受け取った値をPCに返す)
void give_data(){
    char c = mcu2.getc();
    printf("%c\r\n", c);
}

int main(){
    Set_OutPut_Printf(&pc);
    mcu2.attach(&give_data, RawSerial::RxIrq);

    while(1){
        mcu2.putc('A');
        HAL_Delay(50);
    }
}