#pragma once

#include <cstdint>

//target_select

#if defined(STM32F446xx)
extern "C" {
    #include "targets/stm32f446re/PinMap.hpp"
}
#elif defined(STM32F303x8)
extern "C" {
    #include "targets/stm32f303k8/PinMap.hpp"
}
#endif
