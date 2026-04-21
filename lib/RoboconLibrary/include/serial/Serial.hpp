#pragma once

#include "core/PinMap.hpp"
#include "core/System.hpp"
#include <cstdio>



// ========================================
// 設定
// ========================================
#define UART_BUFFER_SIZE 128

class RawSerial {
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

    void attach(Callback cb, IrqType type);

    //送信
    void write(uint8_t data);

    // 受信
    bool readable();
    uint8_t read();
    int getc();

protected:
    USART_TypeDef* instance;

private:
    USART_TypeDef* uart = nullptr;

    uint32_t tx_af;
    uint32_t rx_af;

    void enable_gpio_clock(GPIO_TypeDef* port);
    void enable_uart_clock(USART_TypeDef* uart);
    void start_interrupt();

public:
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

    void push(uint8_t data);
};

void Serial_InitPrintf(RawSerial* uart);
