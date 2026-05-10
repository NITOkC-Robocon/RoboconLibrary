#include <RoboconLibrary.h>

RawSerial pc(USBTX, USBRX, 115200);     //ボーレート:115200
RotaryEncoder encoder(PC_10, PC_11);

const float ENCODER_DEG_PER_COUNT = 2048;    //生エンコーダーの１回転あたりのカウント数(分解能)

//エンコーダーの回転数を計測
float encoder_revolutions(int count){
    float revolutions = count / ENCODER_DEG_PER_COUNT;
    return revolutions;
}

int main(){
    //printfの出力先設定
    Set_OutPut_Printf(&pc);

    while(1){
        int current = encoder.Get_Count();
        printf("encoder=%d, revolutions=%.2f\r\n", current, encoder_revolutions(current));
    }
    
    return 0;
}