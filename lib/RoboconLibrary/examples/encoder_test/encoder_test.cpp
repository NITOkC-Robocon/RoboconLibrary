#include <RoboconLibrary.h>

RawSerial pc(USBTX, USBRX, 115200);     //ボーレート:115200
RotaryEncoder encoder(PC_10, PC_11);

int main(){
    //printfの出力先設定
    Set_OutPut_Printf(&pc);

    while(1){
        double current = encoder.Get_Count();
        printf("encoder = %f\r\n", current);
        HAL_Delay(20);
    }
    
    return 0;
}