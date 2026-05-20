#if defined(STM32F446xx)

#include "driver/timer/TIM_EventScheduler.hpp"

extern "C" void TIM1_UP_TIM10_IRQHandler(){

}
extern "C" void TIM2_IRQHandler(){

}
extern "C" void TIM3_IRQHandler(){

}
extern "C" void TIM4_IRQHandler(){

}
extern "C" void TIM5_IRQHandler(){
    TIM_Clock_IRQHandler();
}
extern "C" void TIM6_DAC_IRQHandler(){

}
extern "C" void TIM8_UP_TIM13_IRQHandler(){

}
extern "C" void TIM1_BRK_TIM9_IRQHandler(){

}
extern "C" void TIM1_TRG_COM_TIM11_IRQHandler(){

}
extern "C" void TIM8_BRK_TIM12_IRQHandler(){

}
extern "C" void TIM8_TRG_COM_TIM14_IRQHandler(){

}


#endif

