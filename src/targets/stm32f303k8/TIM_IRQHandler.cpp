#if defined(STM32F303x8)

#include "driver/timer/TIM_EventScheduler.hpp"

extern "C" void TIM1_UP_TIM16_IRQHandler(){

}
extern "C" void TIM2_IRQHandler(){

}
extern "C" void TIM3_IRQHandler(){

}
extern "C" void TIM1_BRK_TIM15_IRQHandler(){

}
extern "C" void TIM1_UP_TIM16_IRQHandler(){

}
extern "C" void TIM1_TRG_COM_TIM17_IRQHandler(){
    TIM_Clock_IRQHandler();
}

#endif