#include <RoboconLibrary.h>

/*
Servoクラス
内部はpwmoutクラスを使っているが、以下の追加機能がある。

　・pwm周期を自動で20msに設定してくれる
　・setPulseRange()という、パルス幅の範囲指定を行うことができる（安全志向）

もちろん、pwmoutでもしっかり動かせるが、サーボを動かせる範囲の指定が気軽に行えるのでお勧め。
*/

Servo servo(PC_9);   //J1

int main(void) {
    servo.setPulseRange(500, 2500); //パルス幅の範囲指定（パルス幅の範囲はサーボの種類によって異なるので
                                    //                  必ずデータシートを見るようにしよう）
    while(1){
        servo.pulsewidth_us(500);
        wait_ms(500);

        servo.pulsewidth_us(2500);
        wait_ms(500);
    }
}
