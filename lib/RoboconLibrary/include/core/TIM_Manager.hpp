#pragma once

#if defined(STM32F446xx)
    #include "targets/stm32f446re/TIM_Manager.hpp"

#elif (STM32F303x8)
    #include "targets/stm32f303k8/TIM_Manager.hpp"

#endif