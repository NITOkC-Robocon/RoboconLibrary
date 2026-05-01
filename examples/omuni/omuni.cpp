/*
===============================
    足回り制御サンプル(オムニ)
===============================

<足回りの構成イメージ>
左スティックで移動を指示

                前
    1-----------------------0
    |                       |
    |                       |
    |                       |
左  |       ロボット本体       |   右
    |                       |
    |                       |
    |                       |
    2-----------------------3
                後ろ

モータ番号：
0: 右後
1: 左後
2: 左前
3: 右前

===========================
*/
#include <RoboconLibrary.h>

// PCとシリアル通信 (デバッグ用)
RawSerial pc(USBTX, USBRX);
// PS3コントローラからデータを受信するシリアル
RawSerial cont(PC_12, PD_2, 2400);

// モータの回転方向制御用のデジタル出力
DigitalOut Dig[4] = {PB_8, PC_0,  PA_7, PC_5};
// モータの速度制御用のPWM出力
PwmOut P[4] = {PC_9, PA_9, PB_6, PC_7};

// PS3コントローラから受信したデータを格納
int PS3[8] = {0x80, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x00};
int ps3_pool[8] = {0x80, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x00};

// 各モータの目標速度
double target_motor[4];

// 各モータの現在速度（加速制御用）
double current_motor[4];


const double acceleration = 0.20;   // 加速率（値を小さくするとゆっくり加速する）
const double max_speed = 0.8;       //最大速度
const double default_speed = 0.8/1.5;   //通常速度

void Config(void);
void Move(void);
void PS3Data(void);

int main(void) {
    Config(); // 初期設定（割り込み設定、PWM設定など）
    while (true) {
        // Selectボタンが押されたら停止
        if (PS3[2] == 0x0C) { 
            Config(); // 初期化して待機状態へ
        }

        Move(); // モータ制御を実行
        HAL_Delay(30); // 30ms待機（約33Hz）

        // デバッグ用 PS3データを表示（必要ならコメントアウト解除）
        /*
        pc.printf("\033[H"); // 画面クリア
        for (int i = 0; i < 7; i++) {
            pc.printf("%02X, ", PS3[i]);
        }
        pc.printf("\n\r");
        */
    }
}


// 初期設定（割り込み、PWM、待機処理）
void Config(void) {
    Set_OutPut_Printf(&pc);
    // PS3コントローラ用シリアル割り込みを設定
    cont.attach(&PS3Data, RawSerial::RxIrq);

    // 各モータのPWM周期を設定
    for (int i = 0; i < 4; i++) {
        P[i].period_us(1500); // PWM周期 1500us
    }

    // 目標値と現在値をリセット
    for (int i = 0; i < 4; i++) {
        target_motor[i] = 0;
        current_motor[i] = 0;
        P[i].write(0); // PWM出力を0に
        Dig[i] = 0;    // モータ停止
    }

    // PS3データ初期化
    for (int i = 0; i < 8; i++) {
        PS3[i] = 0;
    }

    // Startボタンが押されるまで待機
    while (PS3[2] != 0x03) {
        for (int i = 0; i < 8; i++) {
            pc.printf("%d, ", PS3[i]);
        }
        pc.printf("\r\n");
    }
}


// PS3データの受け取り
void PS3Data(void){
    //受信割り込みのときに来る
    const int PS3_default[8] = {0x80, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x00};
    int SBDBT_Data = cont.getc();
    static int bits = 0;
    static int check_sum = 0x00;
    static int error_count = 0;
    
    if(SBDBT_Data == 128){
        bits = 0;
        check_sum = 0x00; //check_sum初期化
    }

    if (SBDBT_Data >= 0){
        ps3_pool[bits] = SBDBT_Data; //仮収納配列に一旦値を突っ込む
        
        if (bits == 7){
            if((check_sum % 0x80) == ps3_pool[7]){ //7バイト目までの合計の下位7bit（合計値を0x80で割った余りで計算できる）がPS3の8バイト目（チェックサム）と同値か判定
                error_count = 0;
                for(int i = 0; i < 8;i++){
                    PS3[i] = ps3_pool[i]; //チェックサムが正しい（データに間違いが無い）場合、仮配列から本配列にデータを移行
                }
            }
            else{
                error_count++;
                if(error_count >= 5){
                    for(int i = 0; i < 8;i++){
                        PS3[i] = PS3_default[i]; //チェックサムが正しい（データに間違いが無い）場合、仮配列から本配列にデータを移行
                    }
                }
                bits = 0; //念の為初期化（いずれにせよ1バイト目の0x80で初期化されるため、実は必要ない）
            }
        }
        else {
            check_sum += SBDBT_Data; //8バイト目を受け取るまでは、チェックサム変数に加算し続けて合計を取る
            bits++;
        }
    }
}


// モータを動かすメイン関数
void Move(void) {
    int i;
    double x, y;

    // L1ボタン押下 → 全モータ逆回転（右旋回）
    if (PS3[1] == 0x02) { 
        for (i = 0; i < 4; i++) {
            target_motor[i] = default_speed;
        }
    } 
    // R1ボタン押下 → 全モータ正回転（左旋回）
    else if (PS3[1] == 0x08) { 
        for (i = 0; i < 4; i++) {
            target_motor[i] = -default_speed;
        }
    } 
    // 左スティックで方向指示
    else {
        // 横方向入力（-1.0 ~ 1.0）
        x = (double)(PS3[3] - 64) / 64.0; 
        // 縦方向入力（-1.0 ~ 1.0, 符号反転）
        y = -(double)(PS3[4] - 64) / 64.0;

        // 各モータへの割り振り
        // 右後
        target_motor[0] = (-x + y);
        // 左後
        target_motor[1] = (-x - y);
        // 左前
        target_motor[2] = (x - y);
        // 右前
        target_motor[3] = (x + y);
    }


    //出力範囲を正規化(duty比が1.0～0.0の範囲に収まるように、比率を計算して全体を割っている)

    //4つの車輪の中で一番早いものを記録する変数
    //(代入している1.0は、すでにduty比が1.0~0.0の範囲に収まっているとき、そのままの値を使えるようにするため)
    double highest_speed = 1.0; 
    for(i=0; i<4; i++) { 
        if(highest_speed < fabs(target_motor[i])){  //fabsf()は、変数の型がfloatである値の絶対値を入手する関数
            highest_speed = fabs(target_motor[i]);
        } 
    }
    for(i=0; i<4; i++){
        target_motor[i] *= default_speed / highest_speed; //正規化と通常速度の計算を行う
    }

    // 〇ボタン → スピードUP
    if (PS3[2] == 0x40) {
        for (i = 0; i < 4; i++) {
            target_motor[i] *= 1.5;
        }
    }
    // ×ボタン → スピードDOWN
    else if (PS3[2] == 0x20) {
        for (i = 0; i < 4; i++) {
            target_motor[i] *= 0.5;
        }
    }

    // R2ボタン押下 → 右後/右前だけ速度制限（旋回の回転の軸がずれる）
    if (PS3[1] == 0x10) {
        target_motor[0] /= 5.0;
        target_motor[3] /= 5.0;
    }
    // L2ボタン押下 → 左後/左前だけ速度制限（旋回の回転の軸がずれる）
    else if (PS3[1] == 0x04) {
        target_motor[1] /= 5.0;
        target_motor[2] /= 5.0;
    }


    // 加速率を使ってスムーズに目標速度へ近づける
    for (i = 0; i < 4; i++) {
        current_motor[i] += (target_motor[i] - current_motor[i]) * acceleration;

        //回転方向制御
        if (current_motor[i] >= 0) Dig[i] = 1; //正転
        else Dig[i] = 0; // 逆転

        //出力制御
        double duty = fabs(current_motor[i]);

        if(max_speed < duty) duty = max_speed;

        P[i].write(duty);
    }

    // デバッグ出力（必要なら）
    
    //pc.printf("Joystick X: %.2f, Y: %.2f\n", x, y);
    //pc.printf("Target Motors: %.2f %.2f %.2f %.2f\n", target_motor[0], target_motor[1], target_motor[2], target_motor[3]);
    //pc.printf("Current Motors: %.2f %.2f %.2f %.2f\n", current_motor[0], current_motor[1], current_motor[2], current_motor[3]);
    
}
