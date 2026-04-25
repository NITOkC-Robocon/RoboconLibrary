#pragma once

#include <cstdio>
#include "core/PinMap.hpp"
extern "C" {
    #include "stm32f4xx_hal.h"
}

#define UART_BUFFER_SIZE 128

enum IrqType{
    RxIrq,
    TxIrq
};

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

    void enable_gpio_clock(GPIO_TypeDef* port);
    void enable_uart_clock(USART_TypeDef* uart);
    void start_interrupt();

protected:
    USART_TypeDef* instance;

public:
    RawSerial(PinName tx, PinName rx, uint32_t baudrate = 115200);

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

    void baud(uint32_t baudrate);
    void attach(Callback cb, IrqType type);
    void push(uint8_t data);
    
    bool writeable();
    bool readable();

    void write(uint8_t data);
    uint8_t read();

    int putc(int c);
    int getc();
};

void Serial_InitPrintf(RawSerial* uart);
