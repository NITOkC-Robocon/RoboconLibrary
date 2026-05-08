#pragma once

#include "core/System.hpp"

constexpr uint8_t UART_COUNT = 3;
extern USART_TypeDef* uarts[UART_COUNT];

int uartIndex(USART_TypeDef* uart);

void enable_uart_clock(USART_TypeDef* uart);

IRQn_Type getUartIRQ(USART_TypeDef* uart);