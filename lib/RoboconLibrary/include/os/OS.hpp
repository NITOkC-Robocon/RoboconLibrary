#pragma once

#include "FreeRTOS.h"
#include "task.h"

#ifdef __cplusplus
extern "C" {
#endif

void OS_Init();
void OS_Delay(uint32_t ms);

#ifdef __cplusplus
}
#endif