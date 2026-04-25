#include "core/System.hpp"
#include "timer/Clock.hpp"

/* =========================
   TIMハンドラ（制御用）
========================= */
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim8;
TIM_HandleTypeDef htim9;
TIM_HandleTypeDef htim10;
TIM_HandleTypeDef htim11;
TIM_HandleTypeDef htim12;
TIM_HandleTypeDef htim13;
TIM_HandleTypeDef htim14;

//宣言
void SystemClock_Config(void);
void TIM_Global_Init(void);
extern "C" void SysTick_Handler(void);

/* =========================
   初期化関数(一度だけ)
========================= */
static bool initialized = false;
void MCU_Init()
{
    if (initialized) return;

    HAL_Init();     // HAL初期化（SysTick含む）

    __disable_irq();

    SystemClock_Config();    // クロック設定

    TIM_Global_Init();       // 制御用タイマ初期化

    __enable_irq();

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
   TIM初期化
========================= */
void TIM_Global_Init()
{
    htim1.Instance = TIM1;
    htim2.Instance = TIM2;
    htim3.Instance = TIM3;
    htim4.Instance = TIM4;
    htim5.Instance = TIM5;
    htim8.Instance = TIM8;
    htim9.Instance = TIM9;
    htim10.Instance = TIM10;
    htim11.Instance = TIM11;
    htim12.Instance = TIM12;
    htim13.Instance = TIM13;
    htim14.Instance = TIM14;
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