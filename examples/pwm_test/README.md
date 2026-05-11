# pwm_test

##　概要
DCモーターの駆動

##　配線
pwmout用のピン（f446基盤 J1 に対応）
PC_9       

digitalout用のピン（f446基盤 J1 に対応）
PB_8

##　動作
pwm出力の前に、必ずperiod_us();による周波数設定を行う。

pwmは 0.0～1.0 の範囲で設定可能
dirは 0 or 1
