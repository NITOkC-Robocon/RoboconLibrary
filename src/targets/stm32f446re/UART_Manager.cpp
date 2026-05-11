#include "core/UART_Manager.hpp"

#if defined(STM32F446xx)

USART_TypeDef* uarts[UART_COUNT] =
{
    USART1,
    USART2,
    USART3,
    UART4,
    UART5,
    USART6,
};


int uartIndex(USART_TypeDef* uart)
{
    for(int i=0; i<UART_COUNT; i++)
    {
        if(uarts[i] == uart) return i;
    }

    return -1;
}

void enable_uart_clock(USART_TypeDef* uart)
{
    if(uart == USART1) __HAL_RCC_USART1_CLK_ENABLE();
    if(uart == USART2) __HAL_RCC_USART2_CLK_ENABLE();
    if(uart == USART3) __HAL_RCC_USART3_CLK_ENABLE();
    if(uart == UART4)  __HAL_RCC_UART4_CLK_ENABLE();
    if(uart == UART5)  __HAL_RCC_UART5_CLK_ENABLE();
    if(uart == USART6) __HAL_RCC_USART6_CLK_ENABLE();
}

IRQn_Type getUartIRQ(USART_TypeDef* uart)
{
    if(uart == USART1) return USART1_IRQn;
    if(uart == USART2) return USART2_IRQn;
    if(uart == USART3) return USART3_IRQn;
    if(uart == UART4) return UART4_IRQn;
    if(uart == UART5) return UART5_IRQn;
    if(uart == USART3) return USART6_IRQn;

    return NonMaskableInt_IRQn;
}

#endif