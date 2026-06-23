#include "core/System.hpp"

#if defined(STM32F446xx)
#include "driver/timer/Clock.hpp"

//宣言
void SystemClock_Config(void);
extern "C" void SysTick_Handler(void);

/* =========================
   初期化関数(一度だけ)
========================= */
static bool initialized = false;
void MCU_Init()
{
    if (initialized) return;

    HAL_Init();     // HAL初期化（SysTick含む）

    SystemClock_Config();    // クロック設定

    initialized = true;
}


//システムクロックの割り込み呼び出し関数
extern "C" void SysTick_Handler(void)
{
    Clock::Update();
    
#ifdef USE_FREERTOS
    xPortSysTickHandler();
#else
    HAL_IncTick();
#endif
}



/* =========================
   クロック設定
   （HSE 84MHz）
========================= */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();

    FLASH->ACR =
    FLASH_ACR_ICEN |
    FLASH_ACR_DCEN |
    FLASH_ACR_PRFTEN |
    FLASH_ACR_LATENCY_2WS;

    /* ---- PLL設定 ---- */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;

    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) Error_Handler();
    while (__HAL_RCC_GET_FLAG(RCC_FLAG_HSERDY) == RESET);
    while (__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == RESET);

    /* ---- クロック分周 ---- */
    RCC_ClkInitStruct.ClockType =
        RCC_CLOCKTYPE_HCLK |
        RCC_CLOCKTYPE_SYSCLK |
        RCC_CLOCKTYPE_PCLK1 |
        RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;  // 84MHz
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;    // 42MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;    // 84MHz
    
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) Error_Handler();

    SystemCoreClockUpdate();

#ifndef USE_FREERTOS
    HAL_SYSTICK_Config(SystemCoreClock / 1000); //26250は、HCLK=26,250,000であるから（systick=1[kHz]にしたい）
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
#endif
}

/* =========================
   エラーハンドラ
========================= */
void Error_Handler(void)
{
    while (1)
    {
        // デバッグ用：ここで止める
    }
}

/* =========================
    便利関数
========================= */

void wait_ms(int ms)
{
    MCU_Init();
    HAL_Delay(ms);
}


//============================================
//MCU別、ハードウェア依存コード
//============================================

//GPIOクロック有効化
void enableGpioClock(GPIO_TypeDef* port)
{
    if(port == GPIOA) __HAL_RCC_GPIOA_CLK_ENABLE();
    else if(port == GPIOB) __HAL_RCC_GPIOB_CLK_ENABLE();
    else if(port == GPIOC) __HAL_RCC_GPIOC_CLK_ENABLE();
    else if(port == GPIOD) __HAL_RCC_GPIOD_CLK_ENABLE();
    else if(port == GPIOE) __HAL_RCC_GPIOE_CLK_ENABLE();
    else if(port == GPIOF) __HAL_RCC_GPIOF_CLK_ENABLE();
    else if(port == GPIOG) __HAL_RCC_GPIOG_CLK_ENABLE();
    else if(port == GPIOH) __HAL_RCC_GPIOH_CLK_ENABLE();
}

//InterruptIn用IRQ
IRQn_Type getExtiIRQ(uint8_t pin_number)
{
    switch(pin_number)
    {
        case 0: return EXTI0_IRQn;
        case 1: return EXTI1_IRQn;
        case 2: return EXTI2_IRQn;
        case 3: return EXTI3_IRQn;
        case 4: return EXTI4_IRQn;

        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            return EXTI9_5_IRQn;

        default:
            return EXTI15_10_IRQn;
    }
}

#endif