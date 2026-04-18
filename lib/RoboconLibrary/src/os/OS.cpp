#include "os/OS.hpp"

void OS_Init()
{
    // 今は空でOK（後で拡張）
}


void OS_Delay(uint32_t ms)
{
    vTaskDelay(pdMS_TO_TICKS(ms));
}