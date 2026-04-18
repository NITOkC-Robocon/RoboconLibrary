#include "core/System.hpp"
extern "C" {
    #include "FreeRTOS.h"
    #include "task.h"
}

extern "C" void SysTick_Handler(void)
{
    HAL_IncTick();

    if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
    {
        BaseType_t xHigherPriorityTaskWoken = pdFALSE;

        xHigherPriorityTaskWoken = xTaskIncrementTick();

        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}

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

void SystemClock_Config();
void TIM_Global_Init();

bool initailized = false;
void MCU_Init(){
    if(initailized) return;

    HAL_Init();
    SystemClock_Config();
    TIM_Global_Init();

    initailized = true;
}

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
}

/* ===== クロック設定（HSI 16MHz） ===== */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();

    // ===== PLL設定 =====
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;

    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;

    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;

    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) Error_Handler();

    // ===== クロック分周 =====
    RCC_ClkInitStruct.ClockType = 
        RCC_CLOCKTYPE_HCLK |
        RCC_CLOCKTYPE_SYSCLK |
        RCC_CLOCKTYPE_PCLK1 |
        RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;

    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1; // 84MHz
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;   // 42MHz
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;   // 84MHz

    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) Error_Handler();

    // ===== SysTick =====
    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    HAL_NVIC_SetPriority(SysTick_IRQn, configLIBRARY_LOWEST_INTERRUPT_PRIORITY, 0);
}

void Error_Handler(void){
    while(1){};
}

/* ===== タイマー処理関数 ===== */
bool sleep_for_ms(TaskTimer *t, uint32_t period)
{
    if (t->firstCall) {
        t->last = HAL_GetTick();
        t->firstCall = false;
        return false;   // 初回は待たず実行
    }

    if (HAL_GetTick() - t->last < period) {
        return true;    // まだ待つ
    }

    t->last = HAL_GetTick();
    return false;       // 実行OK
}
