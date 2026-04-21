#include "serial/Serial.hpp"

/*
#ifdef USE_FREERTOS
#include "FreeRTOS.h"
#include "semphr.h"
static SemaphoreHandle_t printf_mutex;
#endif
*/


RawSerial* printf_uart = nullptr;

extern "C" int _write(int file, char *ptr, int len)
{
    if (!printf_uart) return 0;

#ifdef USE_FREERTOS
    if (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) {
        if (printf_mutex) {
            xSemaphoreTake(printf_mutex, portMAX_DELAY);
        }
    }
#endif

    for (int i = 0; i < len; i++) {
        printf_uart->write(ptr[i]);
    }

#ifdef USE_FREERTOS
    if (xTaskGetSchedulerState() == taskSCHEDULER_RUNNING) {
        if (printf_mutex) {
            xSemaphoreGive(printf_mutex);
        }
    }
#endif

    return len;
}

void Serial_InitPrintf(RawSerial* uart)
{
    printf_uart = uart;

#ifdef USE_FREERTOS
    static bool initialized = false;
    if (!initialized) {
        printf_mutex = xSemaphoreCreateMutex();
        initialized = true;
    }
#endif
}

// ========================================
// インスタンス管理
// ========================================
static RawSerial* uart_instances[6] = {0};

// ========================================
// IRQハンドラ
// ========================================
extern "C" void USART1_IRQHandler(void)
{
    if(uart_instances[0] != nullptr){
        HAL_UART_IRQHandler(&uart_instances[0]->huart); 
    }
} 
extern "C" void USART2_IRQHandler(void)
{
    if(uart_instances[1] != nullptr){
        HAL_UART_IRQHandler(&uart_instances[1]->huart); 
    }
}
extern "C" void USART3_IRQHandler(void)
{
    if(uart_instances[2] != nullptr){
        HAL_UART_IRQHandler(&uart_instances[2]->huart); 
    }
}
extern "C" void UART4_IRQHandler(void)
{
    if(uart_instances[3] != nullptr){
        HAL_UART_IRQHandler(&uart_instances[3]->huart); 
    }
}
extern "C" void UART5_IRQHandler(void)
{
    if(uart_instances[4] != nullptr){
        HAL_UART_IRQHandler(&uart_instances[4]->huart); 
    }
}
extern "C" void USART6_IRQHandler(void)
{
    if(uart_instances[5] != nullptr){
        HAL_UART_IRQHandler(&uart_instances[5]->huart); 
    }
}

// ========================================
// RawSerial
// ========================================
RawSerial::RawSerial(PinName tx, PinName rx, uint32_t baudrate) {
    MCU_Init();

    const PinInfo& txInfo = PinMap[tx];
    const PinInfo& rxInfo = PinMap[rx];

    for (int i = 0; i < txInfo.uart_count; i++) {
        for (int j = 0; j < rxInfo.uart_count; j++) {
            if (txInfo.uart[i] == rxInfo.uart[j]) {
                uart = txInfo.uart[i];
                tx_af = txInfo.uart_af[i];
                rx_af = rxInfo.uart_af[j];
            }
        }
    }

    if (uart == nullptr) Error_Handler();

    instance = uart;

    if (uart == USART1) uart_instances[0] = this;
    if (uart == USART2) uart_instances[1] = this;
    if (uart == USART3) uart_instances[2] = this;
    if (uart == UART4)  uart_instances[3] = this;
    if (uart == UART5)  uart_instances[4] = this;
    if (uart == USART6) uart_instances[5] = this;

    enable_gpio_clock(txInfo.port);
    enable_gpio_clock(rxInfo.port);

    GPIO_InitTypeDef GPIO_InitStruct = {};
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

    // TX
    GPIO_InitStruct.Pin = txInfo.pin;
    GPIO_InitStruct.Alternate = tx_af;
    HAL_GPIO_Init(txInfo.port, &GPIO_InitStruct);

    // RX
    GPIO_InitStruct.Pin = rxInfo.pin;
    GPIO_InitStruct.Alternate = rx_af;
    HAL_GPIO_Init(rxInfo.port, &GPIO_InitStruct);

    enable_uart_clock(instance);

    huart.Instance = instance;
    huart.Init.BaudRate = baudrate;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;

    if (HAL_UART_Init(&huart) != HAL_OK) {
        Error_Handler();
    }

    if(instance == USART1){
        HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
    else if(instance == USART2){
        HAL_NVIC_SetPriority(USART2_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(USART2_IRQn);
    } 
    else if(instance == USART3){
        HAL_NVIC_SetPriority(USART3_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(USART3_IRQn);
    } 
    else if(instance == UART4){
        HAL_NVIC_SetPriority(UART4_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(UART4_IRQn);
    } 
    else if(instance == UART5){
        HAL_NVIC_SetPriority(UART5_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(UART5_IRQn);
    } 
    else if(instance == USART6){
        HAL_NVIC_SetPriority(USART6_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(USART6_IRQn);
    } 
    else {
        Error_Handler();
    }

    start_interrupt();

}

// ========================================
// 送信（割り込み化）
// ========================================
void RawSerial::write(uint8_t data) {

    __disable_irq();

    uint16_t next = (tx_head + 1) % UART_BUFFER_SIZE;

    if (next == tx_tail) {
        __enable_irq();
        return;
    }

    tx_buffer[tx_head] = data;
    tx_head = next;

    if (!tx_busy) {
        tx_busy = true;

        tx_data = tx_buffer[tx_tail];
        tx_tail = (tx_tail + 1) % UART_BUFFER_SIZE;

        __enable_irq();

        HAL_UART_Transmit_IT(&huart, &tx_data, 1);
        return;
    }

    __enable_irq();
}

// ========================================
// RXリングバッファ
// ========================================
void RawSerial::push(uint8_t data) {
    uint16_t next = (head + 1) % UART_BUFFER_SIZE;

    if (next != tail) {
        buffer[head] = data;
        head = next;
    }
}

//割り込み時の関数呼び出し(関数登録、立ち上がりor立ち下り)
void RawSerial::attach(Callback cb, IrqType type){
    if(type == RxIrq) rx_cb = cb;
    else if (type == TxIrq) tx_cb = cb;
}

bool RawSerial::readable() {
    return head != tail;
}

uint8_t RawSerial::read() {
    if (head == tail) return 0;

    uint8_t data = buffer[tail];
    tail = (tail + 1) % UART_BUFFER_SIZE;
    return data;
}

int RawSerial::getc(){
    while (!readable());
    return read();
}

// ========================================
// 割り込み開始
// ========================================
void RawSerial::start_interrupt() {
    HAL_UART_Receive_IT(&huart, &rx_data, 1);
}

// ========================================
// RXコールバック
// ========================================
extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {

    RawSerial* obj = nullptr;

    if (huart->Instance == USART1) obj = uart_instances[0];
    if (huart->Instance == USART2) obj = uart_instances[1];
    if (huart->Instance == USART3) obj = uart_instances[2];
    if (huart->Instance == UART4)  obj = uart_instances[3];
    if (huart->Instance == UART5)  obj = uart_instances[4];
    if (huart->Instance == USART6) obj = uart_instances[5];

    if (obj != nullptr) {
        obj->push(obj->rx_data);
        if(obj->rx_cb) obj->rx_cb();
        HAL_UART_Receive_IT(huart, &obj->rx_data, 1);
    }
}

// ========================================
// TXコールバック
// ========================================
extern "C" void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {

    RawSerial* obj = nullptr;

    if (huart->Instance == USART1) obj = uart_instances[0];
    if (huart->Instance == USART2) obj = uart_instances[1];
    if (huart->Instance == USART3) obj = uart_instances[2];
    if (huart->Instance == UART4)  obj = uart_instances[3];
    if (huart->Instance == UART5)  obj = uart_instances[4];
    if (huart->Instance == USART6) obj = uart_instances[5];

    if (obj != nullptr) {

        if (obj->tx_head != obj->tx_tail) {

            obj->tx_data = obj->tx_buffer[obj->tx_tail];
            obj->tx_tail = (obj->tx_tail + 1) % UART_BUFFER_SIZE;

            HAL_UART_Transmit_IT(huart, &obj->tx_data, 1);

        } else {
            obj->tx_busy = false;
            if(obj->tx_cb) obj->tx_cb();
        }
    }
}

// ========================================
// クロック
// ========================================
void RawSerial::enable_gpio_clock(GPIO_TypeDef* port) {
    if (port == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
    if (port == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    if (port == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
    if (port == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
}

void RawSerial::enable_uart_clock(USART_TypeDef* uart) {
    if (uart == USART1) __HAL_RCC_USART1_CLK_ENABLE();
    if (uart == USART2) __HAL_RCC_USART2_CLK_ENABLE();
    if (uart == USART3) __HAL_RCC_USART3_CLK_ENABLE();
    if (uart == UART4)  __HAL_RCC_UART4_CLK_ENABLE();
    if (uart == UART5)  __HAL_RCC_UART5_CLK_ENABLE();
    if (uart == USART6) __HAL_RCC_USART6_CLK_ENABLE();
}

