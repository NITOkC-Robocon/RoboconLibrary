#include "core/System.hpp"

#if defined(STM32F303x8)
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
   （HSE 72MHz）
========================= */

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {};

    // HSE ON
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;

    // PLL
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

    // 8MHz * 9 = 72MHz
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;

    // HSE divide
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    // Clock select
    RCC_ClkInitStruct.ClockType =
        RCC_CLOCKTYPE_SYSCLK |
        RCC_CLOCKTYPE_HCLK |
        RCC_CLOCKTYPE_PCLK1 |
        RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;

    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        Error_Handler();
    }

    SystemCoreClockUpdate();

#ifndef USE_FREERTOS
    HAL_SYSTICK_Config(SystemCoreClock / 1000);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
#endif
}



void Error_Handler(void)
{
    while (1)
    {
    }
}

//============================================
//MCU別、ハードウェア依存コード
//============================================

//InterruptIn用IRQ

IRQn_Type getExtiIRQ(uint8_t pin_number)
{
    switch(pin_number)
    {
        case 0: return EXTI0_IRQn;
        case 1: return EXTI1_IRQn;
        case 2: return EXTI2_TSC_IRQn;
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