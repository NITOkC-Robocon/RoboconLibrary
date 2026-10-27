#include <RoboconLibrary.h>
 
RawSerial pc(USBTX, USBRX, 115200);     //ボーレート:115200
RotaryEncoder encoder(PC_10, PC_11);    //エンコーダ用ピン(J11)
 
Ticker encoder_rpm; //周期計測用
 
constexpr float ENCODER_DEG_PER_COUNT = 512;    //生エンコーダーの１回転あたりのカウント数(分解能)
static float rpm = 0.0f;
 
//rpmを取得する関数
void get_encoder_rpm() {
    static int last_count = 0;
    int current_count = encoder.Get_Count();    //エンコーダの値を取得
    int count_diff = current_count - last_count;    //現在値と過去値の差分を計算
    last_count = current_count; //過去値を更新
 
    float rps = (float)count_diff / ENCODER_DEG_PER_COUNT / 0.05f; // 0.05秒ごとにrps計測
    rpm = rps * 60.0f;  //rpm計算
}
 
int main(){
    encoder_rpm.attach_ms(&get_encoder_rpm, 50); // 0.05秒ごとにコールバック関数を呼び出す
 
    while(1){
        pc.printf("encoder=%d, rpm=%.2f\r\n", encoder.Get_Count(), rpm);
        wait_ms(100); // 0.1秒ごとに出力
    }
   
    return 0;
}