#pragma once

#include <cstdarg>
#include <cstdio>

#include "core/PinMap.hpp"


#define UART_BUFFER_SIZE 128

/**
 * @brief シリアル通信用の基本クラス
 * 
 * 
 * 機能説明：
 * UARTを使ってシリアル送受信を行います。
 * 文字列の送受信や、割り込み付きの通信を行うときに利用します。
 * 
 *  * クラス定義：RawSerial(PinName tx, PinName rx, uint32_t baudrate = 115200);
 * @note オブジェクト生成時、デフォルトでボーレートは115200に設定される
 * 
 * 
 * <オブジェクト生成例>
 * 
 * RawSerial pc(USBTX, USBRX);
 * 
 * RawSerial cont(PA_0, PA_1, 9600);
 */
class RawSerial {
private:
    PinInfo txInfo;
    PinInfo rxInfo;
    uint32_t baudrate_keep;

    USART_TypeDef* uart = nullptr;

    uint32_t tx_af;
    uint32_t rx_af;


    mutable bool initialized = false;
    void class_initialized();

    void start_interrupt();

protected:
    USART_TypeDef* instance;

public:
    RawSerial(PinName tx, PinName rx, uint32_t baudrate = 115200);

    enum IrqType{
        RxIrq,
        TxIrq
    };

    //割り込み
    using Callback = void(*)();
    Callback rx_cb = nullptr;
    Callback tx_cb = nullptr;

    UART_HandleTypeDef huart;

    // ===== RXリングバッファ =====
    volatile uint8_t buffer[UART_BUFFER_SIZE];
    volatile uint16_t head = 0;
    volatile uint16_t tail = 0;

    // ===== TXリングバッファ =====
    volatile uint8_t tx_buffer[UART_BUFFER_SIZE];
    volatile uint16_t tx_head = 0;
    volatile uint16_t tx_tail = 0;

    volatile bool tx_busy = false;
    uint8_t tx_data;
    uint8_t rx_data;

    /**
     * @brief printfのように文字列を出力する
     * 
     * <使用例>
     * 
     * uart.printf("Value: %d\n", 123);
     * 
     * @param format 書式文字列
     * @return 出力した文字数
     */
    int printf(const char* format, ...);

    /**
     * @brief 通信速度を設定する
     * 
     * <使用例>
     * 
     * uart.baud(115200);
     * 
     * @param baudrate 通信速度[bps]
     */
    void baud(uint32_t baudrate);

    /**
     * @brief 受信/送信割り込み時に呼ぶ関数を登録する
     * 
     * <使用例>
     * 
     * uart.attach(my_callback, RawSerial::RxIrq);
     * 
     * @param cb 実行したい関数ポインタ
     * @param type 受信割り込みか送信割り込みか
     */
    void attach(Callback cb, IrqType type);

    /**
     * @brief 送信バッファに1バイトを追加する
     * 
     * <使用例>
     * 
     * uart.push('A');
     * 
     * @param data 送信したいデータ
     */
    void push(uint8_t data);

    /**
     * @brief 送信可能かどうかを確認する
     * 
     * <使用例>
     * 
     * uart.writeable();
     * 
     * @return 送信可能ならtrue
     */
    bool writeable();

    /**
     * @brief 受信データがあるか確認する
     * 
     * <使用例>
     * 
     * uart.readable();
     * 
     * @return 受信済みデータがあればtrue
     */
    bool readable();

    /**
     * @brief 1バイトを送信する
     * 
     * <使用例>
     * 
     * uart.write('X');
     * 
     * @param data 送信したいデータ
     */
    void write(uint8_t data);

    /**
     * @brief 1バイトを受信する
     * 
     * <使用例>
     * 
     * uint8_t ch = uart.read();
     * 
     * @return 受信したデータ
     */
    uint8_t read();

    /**
     * @brief 1文字を送信する
     * 
     * @param c 送信したい文字
     * @return 送信結果
     */
    int putc(int c);

    /**
     * @brief 1文字を受信する
     * 
     * @return 受信した文字
     */
    int getc();
};

void Set_OutPut_Printf(RawSerial* uart);
