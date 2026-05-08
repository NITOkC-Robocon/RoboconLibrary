#include "serial/Serial.hpp"

/*
#ifdef USE_FREERTOS
#include "FreeRTOS.h"
#include "semphr.h"
static SemaphoreHandle_t printf_mutex;
#endif
*/

RawSerial* printf_uart = nullptr;

extern "C" FILE __stdout;
extern "C" FILE __stdin;

extern "C" int _write(int file, char *ptr, int len)
{
    if (printf_uart == nullptr) return len;

    for (int i=0; i<len; i++){
        printf_uart->putc(ptr[i]);
    }
    return len;
}

void Set_OutPut_Printf(RawSerial* uart){
    printf_uart = uart;

    setvbuf(stdout, NULL, _IONBF, 0);
#ifdef USE_FREERTOS
    static bool initialized = false;
    if (!initialized) {
        printf_mutex = xSemaphoreCreateMutex();
        initialized = true;
    }
#endif
}

void Error_Handler();

static RawSerial* uart_instances[6] = {0};

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

//コンストラクタ
RawSerial::RawSerial(PinName tx, PinName rx, uint32_t baudrate) {
    txInfo = PinMap[tx];
    rxInfo = PinMap[rx];
    baudrate_keep = baudrate;

    for (int i = 0; i < MAX_UART_PER_PIN; i++) {
        if(txInfo.uart_info[i].uart_mode != TX) continue;

        for (int j = 0; j < MAX_UART_PER_PIN; j++) {
            if(rxInfo.uart_info[j].uart_mode != RX) continue;

            if (txInfo.uart_info[i].uart == rxInfo.uart_info[j].uart) {
                uart = txInfo.uart_info[i].uart;
                tx_af = txInfo.uart_info[i].uart_af;
                rx_af = rxInfo.uart_info[j].uart_af;

                break;
            }
        }
        if(uart != nullptr) break;
    }

    if (uart == nullptr) Error_Handler();

    instance = uart;

    if (uart == USART1) uart_instances[0] = this;
    if (uart == USART2) uart_instances[1] = this;
    if (uart == USART3) uart_instances[2] = this;
    if (uart == UART4)  uart_instances[3] = this;
    if (uart == UART5)  uart_instances[4] = this;
    if (uart == USART6) uart_instances[5] = this;
}

//初期化関連

void RawSerial::class_initialized() {
    if(initialized) return;
    MCU_Init();

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
    huart.Init.BaudRate = baudrate_keep;
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

    initialized = true;
}

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

void RawSerial::start_interrupt() {
    HAL_UART_Receive_IT(&huart, &rx_data, 1);
}

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

//ボーレート設定・関数登録

void RawSerial::baud(uint32_t baudrate) {
    baudrate_keep = baudrate;

    if (initialized) {
        huart.Init.BaudRate = baudrate_keep;

        if (HAL_UART_Init(&huart) != HAL_OK) {
            Error_Handler();
        }
    }
}

void RawSerial::attach(Callback cb, IrqType type){
    class_initialized();
    if(type == RxIrq) rx_cb = cb;
    else if (type == TxIrq) tx_cb = cb;
}



//送受信用メソッド
int RawSerial::printf(const char* format, ...)
{
    class_initialized();

    char buffer[256];

    va_list args;
    va_start(args, format);

    int len = vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);

    if (len < 0) {
        return len;
    }

    if (len >= static_cast<int>(sizeof(buffer))) {
        len = sizeof(buffer) - 1;
    }

    for (int i = 0; i < len; ++i) {
        putc(buffer[i]);
    }

    return len;
}

bool RawSerial::writeable() {
    class_initialized();

    uint16_t next = (tx_head + 1) % UART_BUFFER_SIZE;
    return next != tx_tail;
}

bool RawSerial::readable() {
    class_initialized();

    return head != tail;
}

void RawSerial::write(uint8_t data) {
    class_initialized();

    __disable_irq();

    uint16_t next = (tx_head + 1) % UART_BUFFER_SIZE;

    while (next == tx_tail) {
        __enable_irq();
        __disable_irq();
        next = (tx_head + 1) % UART_BUFFER_SIZE;
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

uint8_t RawSerial::read() {
    class_initialized();

    if (head == tail) return 0;

    uint8_t data = buffer[tail];
    tail = (tail + 1) % UART_BUFFER_SIZE;
    return data;
}

int RawSerial::putc(int c) {
    write((uint8_t)c);
    return c;
}

int RawSerial::getc(){
    while (!readable());
    return read();
}

void RawSerial::push(uint8_t data) {
    uint16_t next = (head + 1) % UART_BUFFER_SIZE;

    if (next != tail) {
        buffer[head] = data;
        head = next;
    }
}