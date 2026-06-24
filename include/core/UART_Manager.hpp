#pragma once

#if defined(STM32F446xx)
extern "C" {
    #include "stm32f4xx_hal.h"
}

constexpr uint8_t UART_COUNT = 6;
extern USART_TypeDef* uarts[UART_COUNT];

int uartIndex(USART_TypeDef* uart);

void enable_uart_clock(USART_TypeDef* uart);

IRQn_Type getUartIRQ(USART_TypeDef* uart);

#elif (STM32F303x8)
extern "C" {
    #include "stm32f3xx_hal.h"
}

    constexpr uint8_t UART_COUNT = 3;
    extern USART_TypeDef* uarts[UART_COUNT];

    int uartIndex(USART_TypeDef* uart);

    void enable_uart_clock(USART_TypeDef* uart);

    IRQn_Type getUartIRQ(USART_TypeDef* uart);

#endif
