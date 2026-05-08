#include "core/PinMap.hpp"
#if defined(STM32F303x8)

extern const uint32_t PinPull[PULL_MAX] = {GPIO_NOPULL, GPIO_PULLUP, GPIO_PULLDOWN};

const PinInfo PinMap[PIN_MAX] = {

    // -------- Port A --------
     { "PA_0",  GPIOA, GPIO_PIN_0,  {{TIM2,TIM_CHANNEL_1,GPIO_AF1_TIM2}, {nullptr,0,0}},                                                            {{nullptr,0,NONE}}            },
     { "PA_1",  GPIOA, GPIO_PIN_1,  {{TIM2,TIM_CHANNEL_2,GPIO_AF1_TIM2}, {TIM15,TIM_CHANNEL_1,GPIO_AF9_TIM15}, {nullptr,0,0}},                      {{nullptr,0,NONE}}            },
     { "PA_2",  GPIOA, GPIO_PIN_2,  {{TIM2,TIM_CHANNEL_3,GPIO_AF1_TIM2}, {TIM15,TIM_CHANNEL_1,GPIO_AF9_TIM15}, {nullptr,0,0}},                      {{USART2,GPIO_AF7_USART2,TX}} },
     { "PA_3",  GPIOA, GPIO_PIN_3,  {{TIM2,TIM_CHANNEL_4,GPIO_AF1_TIM2}, {TIM15,TIM_CHANNEL_2,GPIO_AF9_TIM15}, {nullptr,0,0}},                      {{USART2,GPIO_AF7_USART2,RX}} },
     { "PA_4",  GPIOA, GPIO_PIN_4,  {{TIM3,TIM_CHANNEL_2,GPIO_AF2_TIM3}, {nullptr,0,0}},                                                            {{nullptr,0,NONE}}            },
     { "PA_5",  GPIOA, GPIO_PIN_5,  {{TIM2,TIM_CHANNEL_1,GPIO_AF1_TIM2}, {nullptr,0,0}},                                                            {{nullptr,0,NONE}}            },
     { "PA_6",  GPIOA, GPIO_PIN_6,  {{TIM3,TIM_CHANNEL_1,GPIO_AF2_TIM3}, {TIM16,TIM_CHANNEL_1,GPIO_AF1_TIM16}, {nullptr,0,0}},                      {{nullptr,0,NONE}}            },
     { "PA_7",  GPIOA, GPIO_PIN_7,  {{TIM3,TIM_CHANNEL_2,GPIO_AF2_TIM3}, {TIM1,TIM_CHANNEL_1,GPIO_AF6_TIM1}, {TIM17,TIM_CHANNEL_1,GPIO_AF1_TIM17}}, {{nullptr,0,NONE}}            },
     { "PA_8",  GPIOA, GPIO_PIN_8,  {{TIM1,TIM_CHANNEL_1,GPIO_AF6_TIM1}, {nullptr,0,0}},                                                            {{nullptr,0,NONE}}            },
     { "PA_9",  GPIOA, GPIO_PIN_9,  {{TIM1,TIM_CHANNEL_2,GPIO_AF6_TIM1}, {TIM2,TIM_CHANNEL_3,GPIO_AF10_TIM2}, {nullptr,0,0}},                       {{USART1,GPIO_AF7_USART1,TX}} },
     { "PA_10", GPIOA, GPIO_PIN_10, {{TIM1,TIM_CHANNEL_3,GPIO_AF6_TIM1}, {TIM2,TIM_CHANNEL_4,GPIO_AF10_TIM2}, {nullptr,0,0}},                       {{USART1,GPIO_AF7_USART1,RX}} },
     { "PA_11", GPIOA, GPIO_PIN_11, {{TIM1,TIM_CHANNEL_1,GPIO_AF6_TIM1}, {TIM1,TIM_CHANNEL_4,GPIO_AF11_TIM1}, {nullptr,0,0}},                       {{nullptr,0,NONE}}            },
     { "PA_12", GPIOA, GPIO_PIN_12, {{TIM1,TIM_CHANNEL_2,GPIO_AF6_TIM1}, {TIM16,TIM_CHANNEL_1,GPIO_AF1_TIM16}, {nullptr,0,0}},                      {{nullptr,0,NONE}}            },

    // -------- Port B --------
     { "PB_0",  GPIOB, GPIO_PIN_0,  {{TIM1,TIM_CHANNEL_2,GPIO_AF6_TIM1}, {TIM3,TIM_CHANNEL_3,GPIO_AF2_TIM3}, {nullptr,0,0}},    {{nullptr,0,NONE}}            },
     { "PB_1",  GPIOB, GPIO_PIN_1,  {{TIM1,TIM_CHANNEL_3,GPIO_AF6_TIM1}, {TIM3,TIM_CHANNEL_4,GPIO_AF2_TIM3}, {nullptr,0,0}},    {{nullptr,0,NONE}}            },
     { "PB_3",  GPIOB, GPIO_PIN_3,  {{TIM2,TIM_CHANNEL_2,GPIO_AF1_TIM2}, {nullptr,0,0}},                                        {{USART2,GPIO_AF7_USART2,TX}} },
     { "PB_4",  GPIOB, GPIO_PIN_4,  {{TIM3,TIM_CHANNEL_1,GPIO_AF2_TIM3}, {TIM16,TIM_CHANNEL_1,GPIO_AF2_TIM16}, {nullptr,0,0}},  {{USART2,GPIO_AF7_USART2,RX}} },
     { "PB_5",  GPIOB, GPIO_PIN_5,  {{TIM3,TIM_CHANNEL_2,GPIO_AF2_TIM3}, {TIM17,TIM_CHANNEL_1,GPIO_AF10_TIM17}, {nullptr,0,0}}, {{nullptr,0,NONE}}            },
     { "PB_6",  GPIOB, GPIO_PIN_6,  {{TIM16,TIM_CHANNEL_1,GPIO_AF1_TIM16}, {nullptr,0,0}},                                      {{USART1,GPIO_AF7_USART1,TX}} },
     { "PB_7",  GPIOB, GPIO_PIN_7,  {{TIM3,TIM_CHANNEL_4,GPIO_AF10_TIM3}, {TIM17,TIM_CHANNEL_1,GPIO_AF1_TIM17}, {nullptr,0,0}}, {{USART1,GPIO_AF7_USART1,RX}} },

    // -------- Port F --------
    { "PF_0", GPIOF, GPIO_PIN_0, {{TIM1,TIM_CHANNEL_3,GPIO_AF6_TIM1}, {nullptr,0,0}}, {{nullptr,0,NONE}} },
    { "PF_1", GPIOF, GPIO_PIN_1, {{nullptr,0,0}},                                     {{nullptr,0,NONE}} },
};

#endif