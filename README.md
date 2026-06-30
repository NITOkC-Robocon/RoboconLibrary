# RoboconLibrary

A lightweight STM32Cube-based mbed-like library for PlatformIO.
（PlatfomIO向け、STM32Cubeベースのmbed風ライブラリ。）

RoboconLibrary is designed for long-term embedded development after Mbed OS end-of-life, providing a familiar mbed-style API while using STM32Cube HAL as backend.
（RoboconLibraryは、Mbed OSのサポート終了後も長期的な組み込み開発を継続できるよう設計されており、バックエンドとしてSTM32Cube HALを使用しながら、使い慣れたmbedスタイルのAPIを提供する。）

---

## Features（特徴）

- mbed-like API design
- STM32Cube HAL backend
- PlatformIO support
- Lightweight and simple abstraction
- Designed for Robocon development
- Multi-target STM32 support

---

## Supported Targets（サポート対象）

Currently tested on:

- STM32F303K8
- STM32F446RE

---

## Installation（インストール）

Add this library to your `platformio.ini`.
（[env:xx]毎に以下のコードを platformio.ini に書き込むこと）

```ini
lib_deps =
    https://github.com/NITOkC-Robocon/RoboconLibrary.git
```

---

## Library Structure（ライブラリ構造）
Note:
Timer is a software-based elapsed time measurement API.
（Timer＝ソフトウェアベースの経過時間計測API）

TIM_core is an internal hardware abstraction layer that manages STM32 TIM peripherals.
（TIM_core＝STM32のTIM周辺機器を管理する内部ハードウェア抽象化レイヤー）
It is used by PWM generation and hardware-based timing features.
（PWM生成機能やハードウェアベースのタイミング機能で使用される）

PinMap defines logical pin names and maps them to MCU-specific GPIO pins.
（PinMapは論理ピン名を定義し、それらをMCU固有のGPIOピンにマッピングします。）
Details are described in PinMap documentation.
（詳細はPinMapのドキュメントに記載されています。）

```text
RoboconLibrary/
|
├── examples/
|   ├── Analog/
|   |   ├── mcu_1.cpp
|   |   ├── mcu_2.cpp
|   |   └── README.md
|   |
|   ├── encoder_test/
|   |   ├── encoder_test.cpp
|   |   └── README.md
|   |
|   ├── led_toggle/
|   |   ├── led_toggle.cpp
|   |   └── README.md
|   |
|   ├── MCU_com/
|   |   ├── mcu_1.cpp
|   |   ├── mcu_2.cpp
|   |   └── README.md
|   |
|   ├── omni/
|   |   ├── omni.cpp
|   |   └── README.md
|   |
|   ├── PS3_com/
|   |   ├── PS3_com.cpp
|   |   └── README.md
|   |
|   └── pwm_test/
|       ├── pwm_test.cpp
|       └── README.md
|   
├── include/
|   ├── core/
|   |   ├── ADC_DAC_Init.hpp
|   |   ├── PinMap.hpp
|   |   ├── System.hpp
|   |   ├── TIM_Init.hpp
|   |   ├── TIM_Manager.hpp
|   |   └── UART_Manager.hpp
|   |
|   ├── driver/
|   |   ├── Analog/
|   |   |   ├── AnalogIn.hpp
|   |   |   └── AnalogOut.hpp
|   |   |
|   |   ├── digital/
|   |   |   ├── DigitalIn.hpp
|   |   |   └── DigitalOut.hpp
|   |   |
|   |   ├── encoder/
|   |   |   └── RotaryEncoder.hpp
|   |   |
|   |   ├── interrupt/
|   |   |   └── InterruptIn.hpp
|   |   |
|   |   ├── pwm/
|   |   |   └── PwmOut.hpp
|   |   |
|   |   ├── serial/
|   |   |   └── RawSerial.hpp
|   |   |
|   |   └── timer/
|   |       ├── Clock.hpp
|   |       ├── Ticker.hpp
|   |       ├── TIM_Events.hpp
|   |       ├── TIM_EventScheduler.hpp
|   |       ├── Timeout.hpp
|   |       └── Timer.hpp
|   |
|   ├── targets/
|   |   ├── stm32f303k8/
|   |   |   └── PinMap.hpp
|   |   |
|   |   └── stm32f446re/
|   |       └── PinMap.hpp
|   |    
|   └── RoboconLibrary.h
|
├── src/
|   ├── driver/
|   |   ├── Analog/
|   |   |   ├── AnalogIn.cpp
|   |   |   └── AnalogOut.cpp
|   |   |
|   |   ├── digital/
|   |   |   ├── DigitalIn.cpp
|   |   |   └── DigitalOut.cpp
|   |   |
|   |   ├── encoder/
|   |   |   └── RotaryEncoder.cpp
|   |   |
|   |   ├── interrupt/
|   |   |   └── InterruptIn.cpp
|   |   |
|   |   ├── pwm/
|   |   |   └── PwmOut.cpp
|   |   |
|   |   ├── serial/
|   |   |   └── RawSerial.cpp
|   |   |
|   |   └── timer/
|   |       ├── Clock.cpp
|   |       ├── Ticker.hpp
|   |       ├── TIM_Events.cpp
|   |       ├── TIM_EventScheduler.cpp
|   |       ├── Timeout.cpp
|   |       └── Timer.cpp
|   |
|   └── targets/
|       ├── stm32f303k8/
|       |   ├── ADC_DAC_Init.cpp
|       |   ├── PinMap.cpp
|       |   ├── System.cpp
|       |   ├── TIM_Init.cpp
|       |   ├── TIM_Manager.cpp
|       |   └── UART_Manager.cpp
|       |
|       └── stm32f446re/
|           ├── ADC_DAC_Init.cpp
|           ├── PinMap.cpp
|           ├── System.cpp
|           ├── TIM_Init.cpp
|           ├── TIM_Manager.cpp
|           └── UART_Manager.cpp
|
├── .gitignore
|
├── Library.json
|
├── LICENSE
|
└── platformio.ini
```


---

## Available Modules（利用可能なモジュール）

### AnalogOut
Control analog output pins.

Typical use cases（利用例）:
- Conrtol circuit voltage　（回路の電圧制御）

Methods（メソッド）:
- set_buffer_extence(mode) Set DAC buffer extence (true or false)（使用するDACのバッファの有無を書き換える）
- write(value) : Set output level (0.0 ~ 1.0)（出力値を設定）
- write_u16(value) : Set output level (0 ~ 65535)

---

### AnalogIn
Control analog input pins.

Typical use cases（利用例）:
- Distance sensor voltage detection（距離センサの電圧検知）

Methods（メソッド）:
- read() : Get current input state（入力値の取得：0.0 ~ 1.0）
- read_u16() : Get current input state （入力値の取得：0 ~ 65535）

---

### DigitalOut
Control digital output pins.

Typical use cases（利用例）:
- Control LED
- Motor rotation direction control （モーターの回転方向制御）

Methods（メソッド）:
- write(value) : Set output level (0 or 1)（出力値を設定）
- read() : Get current output state（出力値を取得）
- toggle() : Invert current output state（電流出力状態を反転）
- high() : Set output HIGH（出力をHigh状態にする）
- low() : Set output LOW（出力をlow状態にする）

---

### DigitalIn
Control digital input pins.

Typical use cases（利用例）:
- Limit switch input detection（リミットスイッチの入力検知）

Methods（メソッド）:
- read() : Get current input state（入力値を取得）
- mode(pull) : Set input pin pull configuration (PULLUP / PULLDOWN / PULLNONE)（入力ピンの内部プル抵抗の有効化状態を設定）

---

### Timer
Measure elapsed time.（経過時間を計測）

Typical use cases（利用例）:
- Time control in PID control（PID制御における時間制御）
- Motor RPM measurement（モーターのrpm計測）

Methods（メソッド）:
- start() : Start counting time（計測開始）
- stop() : Stop counting（計測停止）
- reset() : Reset counter to zero（計測値をリセット）
- read() : Get elapsed time in seconds（経過時間を取得：単位[sec]）
- read_ms() : Get elapsed time in milliseconds（経過時間を取得：単位[ms]）
- read_us() : Get elapsed time in microseconds（経過時間を取得：単位[us]）
- isRunning() : Check if timer is running（計測状態を取得）

---

### Ticker
Call a function periodically using a hardware timer.
（ハードウェアタイマーを用いて一定周期で関数を実行）

Typical use cases（利用例）:
- Periodic control loop（周期制御）
- Sensor polling（センサの定期読み取り）
- LED blinking（LED点滅）

Methods（メソッド）:
- attach_ms(callback, ms) : Execute callback periodically in millisecond（周期的にコールバックを実行：単位[ms]）
- attach_us(callback, us) : Execute callback periodically in microsecond（周期的にコールバックを実行：単位[us]）
- active() : Restart periodic execution
- detach() : Stop periodic execution

---

### Timeout
Execute a function once after a specified delay.
（指定時間後に一度だけ関数を実行）

Typical use cases（利用例）:
- Delayed execution（遅延実行）
- Non-blocking wait（ノンブロッキング待機）
- One-shot event（ワンショットイベント）

Methods（メソッド）:
- attach_ms(callback, ms) : Execute callback once after delay（指定時間後にコールバックを実行：単位[ms]）
- attach_us(callback, us) : Execute callback once after delay（指定時間後にコールバックを実行：単位[us]）
- active() : Restart timeout（コールバック関数の再設定）
- detach() : Cancel scheduled callback（登録したコールバックの解除）

---

### PwmOut
Generate PWM signals.（PWM信号を生成）

Typical use cases（利用例）:
- Control motor （モーター制御）

Methods（メソッド）:
- write(duty) : Set duty cycle (0.0 to 1.0)（出力をduty比0.0～1.0で設定）
- read() : Get current duty cycle（出力値を取得）
- period_ms(ms) : Set PWM period in milliseconds（PWM周期を設定：単位[ms]）
- period_us(us) : Set PWM period in microseconds（PWM周期を設定：単位[us]）
- pulsewidth() : Get current pulse width in seconds（現在のパルス幅を取得）
- pulsewidth_us(us) : Set pulse width in microseconds（パルス幅を設定：単位[us]）
- pulsewidth_tick(ticks) : Set pulse width in timer ticks（パルス幅を設定：単位[ticks]）

---

### Servo
Generate servo control signals.（サーボ制御信号の生成）

Typical use cases（利用例）:
- Servo motor position control（サーボモーターの位置制御）
- Actuator angle control in robotics（ロボットにおけるアクチュエータの角度制御）

Methods（メソッド）:
- period_ms(ms) : Set servo PWM period in milliseconds（PWM周期の設定：単位[ms]）
- period_us(us) : Set servo PWM period in microseconds（PWM周期の設定：単位[us]）
- setPulseRange(min, max) : Define pulse width range for angle mapping（パルス幅の限界値を設定：単位[us]）
- pulsewidth_us(us) : Directly set servo pulse width in microseconds（パルス幅を設定：単位[us]）

---

### RawSerial
Low-level blocking UART interface for direct serial communication.
（直接シリアル通信用の低レベルブロッキングUARTインターフェース。）

Typical use cases（利用例）:
- Debug output
- Sensor communication
- Simple command interface

Methods（メソッド）:
- baud(rate) : Set UART baud rate（ボーレート設定）
- attach(callback) : Attach interrupt callback for RX events（RXにおける割り込み時に実行する関数の設定）
- putc(c) : Send one character（一文字送る）
- getc() : Receive one character (blocking)（一文字受け取る）
- readable() : Check if data is available to read（データを読み込めるかを判定）
- writeable() : Check if transmit buffer is available（データを送れるかを判定）
- printf(fmt, ...) : Formatted output (like stdio printf)（文字や数字の出力）
- write(data, size) : Send multiple bytes（複数バイト送信）
- read(data, size) : Receive multiple bytes (blocking)（複数バイト受信）

---

### InterruptIn
Interrupt-driven digital input.（割り込み駆動型デジタル入力）

Typical use cases:
- Receive sensor signal 

Methods:
- mode(mode) : Configure input pin (pull-up / pull-down / floating)
- rise(callback) : Set callback on rising edge signal（割り込み関数の設定：立ち上がり時）
- fall(callback) : Set callback on falling edge signal（割り込み関数の設定：立ち下り時）
- read() : Read current pin state（ピンの状態判定）

---

### RotaryEncoder
Interrupt-driven rotary encoder interface.

Typical use cases:
- Read rotary encoder pulse counts

Methods:
- Get_Count() : Get current encoder pulse count（エンコーダーのカウント数を取得）
- Reset() : Reset count to zero（カウントをリセット）
- Get_Circumference(Diameter,　Resolution) : Convert pulse count into linear travel distance using wheel diameter and encoder resolution（ホイール径と分解能からパルス数を直線移動距離に変換）

---


## Design Philosophy（設計思想）
This library is designed to preserve existing Robocon code assets and maintain the ease of learning provided by the familiar mbed-style API after the end-of-life of Mbed OS.

It follows the following principles:

- Keep a familiar mbed-like API to reduce migration cost
- Separate user API layer from hardware abstraction layer (HAL-based backend)
- Minimize dependency complexity to ensure lightweight integration in PlatformIO projects
- Provide consistent behavior across multiple STM32 targets
- Emphasize transparency in control without overly concealing the hardware's behavior.

＜日本語訳＞
このライブラリは、既存のRoboconコード資産を維持し、mbed OSのサポート終了後も、使い慣れたmbedスタイルのAPIによる学習の容易さを維持することを目的としています。

以下の原則に基づいています。

- 移行コストを削減するために、使い慣れたmbedライクなAPIを維持する
- ユーザーAPI層とハードウェア抽象化層（HALベースのバックエンド）を分離する
- PlatformIOプロジェクトへの軽量な統合を可能にするため、依存関係の複雑さを最小限に抑える
- 複数のSTM32ターゲット間で一貫した動作を提供する
- ハードウェアの挙動を隠しすぎず、ユーザーが制御の仕組みを推測できるレベルの透明性を維持する


## Basic Example（基礎例）
All modules are included via `RoboconLibrary.h` (umbrella header).
（すべてのモジュールは RoboconLibrary.h に導入されています。）
Direct module includes are not required.
（直接モジュールを導入する必要はありません。）

This design ensures simplicity and consistency across all supported STM32 targets.
（この設計により、サポートされているすべてのSTM32ターゲットにおいて、シンプルさと一貫性が確保されます。）

```cpp
#include <RoboconLibrary.h> 

DigitalOut led(LED1);

int main()
{
    while (1) {
        led.toggle();
    }
}
```