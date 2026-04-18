#include <RoboconLibrary.h>

RawSerial pc(USBTX, USBRX, 115200);
RawSerial cont(PC_12, PD_2, 2400);

int PS3[8] = {0x80, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x00};
int ps3_pool[8] = {0x80, 0x00, 0x00, 0x40, 0x40, 0x40, 0x40, 0x00};

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

int main(){
    set_printf_uart(&pc);
    cont.attach(&PS3Data, RawSerial::RxIrq);

    while(1){
        printf("%d, %d, %d, %d, %d, %d, %d, %d,\r\n",
            PS3[0], PS3[1], PS3[2], PS3[3], PS3[4], PS3[5], PS3[6], PS3[7]);
        HAL_Delay(20);
    }

    return 0;
}