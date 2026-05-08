#include "core/PinMap.hpp"

extern const uint32_t PinPull[PULL_MAX] = {GPIO_NOPULL, GPIO_PULLUP, GPIO_PULLDOWN};

const PinInfo PinMap[PIN_MAX] = {

    // -------- Port A --------
    { "PA_0",  GPIOA, GPIO_PIN_0,  {{TIM2,TIM_CHANNEL_1,GPIO_AF1_TIM2}, {TIM5,TIM_CHANNEL_1,GPIO_AF2_TIM5},   {nullptr,0,0}},                                                            {{UART4,GPIO_AF8_UART4,TX}, {nullptr,0,NONE}}   },
    { "PA_1",  GPIOA, GPIO_PIN_1,  {{TIM2,TIM_CHANNEL_2,GPIO_AF1_TIM2}, {TIM5,TIM_CHANNEL_2,GPIO_AF2_TIM5},   {nullptr,0,0}},                                                            {{UART4,GPIO_AF8_UART4,RX}, {nullptr,0,NONE}}   },
    { "PA_2",  GPIOA, GPIO_PIN_2,  {{TIM2,TIM_CHANNEL_3,GPIO_AF1_TIM2}, {TIM5,TIM_CHANNEL_3,GPIO_AF2_TIM5},   {TIM9,TIM_CHANNEL_1,GPIO_AF3_TIM9}, {nullptr,0,0}},                        {{USART2,GPIO_AF7_USART2,TX}, {nullptr,0,NONE}} },
    { "PA_3",  GPIOA, GPIO_PIN_3,  {{TIM2,TIM_CHANNEL_4,GPIO_AF1_TIM2}, {TIM5,TIM_CHANNEL_4,GPIO_AF2_TIM5},   {TIM9,TIM_CHANNEL_2,GPIO_AF3_TIM9}, {nullptr,0,0}},                        {{USART2,GPIO_AF7_USART2,RX}, {nullptr,0,NONE}} },
    { "PA_4",  GPIOA, GPIO_PIN_4,  {{nullptr,0,0}},                                                                                                                                      {{nullptr,0,NONE}}                              },
    { "PA_5",  GPIOA, GPIO_PIN_5,  {{TIM2,TIM_CHANNEL_1,GPIO_AF1_TIM2}, {TIM8,TIM_CHANNEL_1,GPIO_AF3_TIM8},   {nullptr,0,0}},                                                            {{nullptr,0,NONE}}                              },
    { "PA_6",  GPIOA, GPIO_PIN_6,  {{TIM3,TIM_CHANNEL_1,GPIO_AF2_TIM3}, {TIM13,TIM_CHANNEL_1,GPIO_AF9_TIM13}, {nullptr,0,0}},                                                            {{nullptr,0,NONE}}                              },
    { "PA_7",  GPIOA, GPIO_PIN_7,  {{TIM1,TIM_CHANNEL_1,GPIO_AF1_TIM1}, {TIM3,TIM_CHANNEL_2,GPIO_AF2_TIM3},   {TIM8,TIM_CHANNEL_1,GPIO_AF3_TIM8}, {TIM14,TIM_CHANNEL_1,GPIO_AF9_TIM14}}, {{nullptr,0,NONE}}                              },
    { "PA_8",  GPIOA, GPIO_PIN_8,  {{TIM1,TIM_CHANNEL_1,GPIO_AF1_TIM1}, {nullptr,0,0}},                                                                                                  {{nullptr,0,NONE}}                              },
    { "PA_9",  GPIOA, GPIO_PIN_9,  {{TIM1,TIM_CHANNEL_2,GPIO_AF1_TIM1}, {nullptr,0,0}},                                                                                                  {{USART1,GPIO_AF7_USART1,TX}, {nullptr,0,NONE}} },
    { "PA_10", GPIOA, GPIO_PIN_10, {{TIM1,TIM_CHANNEL_3,GPIO_AF1_TIM1}, {nullptr,0,0}},                                                                                                  {{USART1,GPIO_AF7_USART1,RX}, {nullptr,0,NONE}} },
    { "PA_11", GPIOA, GPIO_PIN_11, {{TIM1,TIM_CHANNEL_4,GPIO_AF1_TIM1}, {nullptr,0,0}},                                                                                                  {{nullptr,0,NONE}}                              },
    { "PA_12", GPIOA, GPIO_PIN_12, {{nullptr,0,0}},                                                                                                                                      {{nullptr,0,NONE}}                              },
    { "PA_13", GPIOA, GPIO_PIN_13, {{nullptr,0,0}},                                                                                                                                      {{nullptr,0,NONE}}                              },
    { "PA_14", GPIOA, GPIO_PIN_14, {{nullptr,0,0}},                                                                                                                                      {{nullptr,0,NONE}}                              },
    { "PA_15", GPIOA, GPIO_PIN_15, {{TIM2,TIM_CHANNEL_1,GPIO_AF1_TIM2}, {nullptr,0,0}},                                                                                                  {{nullptr,0,NONE}}                              },

    // -------- Port B --------
    { "PB_0",  GPIOB, GPIO_PIN_0,  {{TIM1,TIM_CHANNEL_2,GPIO_AF1_TIM1}, {TIM3,TIM_CHANNEL_3,GPIO_AF2_TIM3}, {TIM8,TIM_CHANNEL_2,GPIO_AF3_TIM8}, {nullptr,0,0}},   {{nullptr,0,NONE}}            },
    { "PB_1",  GPIOB, GPIO_PIN_1,  {{TIM1,TIM_CHANNEL_3,GPIO_AF1_TIM1}, {TIM3,TIM_CHANNEL_4,GPIO_AF2_TIM3}, {TIM8,TIM_CHANNEL_3,GPIO_AF3_TIM8}, {nullptr,0,0}},   {{nullptr,0,NONE}}            },
    { "PB_2",  GPIOB, GPIO_PIN_2,  {{TIM2,TIM_CHANNEL_4,GPIO_AF1_TIM2}, {nullptr,0,0}},                                                                           {{nullptr,0,NONE}}            },
    { "PB_3",  GPIOB, GPIO_PIN_3,  {{TIM2,TIM_CHANNEL_2,GPIO_AF1_TIM2}, {nullptr,0,0}},                                                                           {{nullptr,0,NONE}}            },
    { "PB_4",  GPIOB, GPIO_PIN_4,  {{TIM3,TIM_CHANNEL_1,GPIO_AF2_TIM3}, {nullptr,0,0}},                                                                           {{nullptr,0,NONE}}            },
    { "PB_5",  GPIOB, GPIO_PIN_5,  {{TIM3,TIM_CHANNEL_2,GPIO_AF2_TIM3}, {nullptr,0,0}},                                                                           {{nullptr,0,NONE}}            },
    { "PB_6",  GPIOB, GPIO_PIN_6,  {{TIM4,TIM_CHANNEL_1,GPIO_AF2_TIM4}, {nullptr,0,0}},                                                                           {{USART1,GPIO_AF7_USART1,TX}} },
    { "PB_7",  GPIOB, GPIO_PIN_7,  {{TIM4,TIM_CHANNEL_2,GPIO_AF2_TIM4}, {nullptr,0,0}},                                                                           {{USART1,GPIO_AF7_USART1,RX}} },
    { "PB_8",  GPIOB, GPIO_PIN_8,  {{TIM2,TIM_CHANNEL_1,GPIO_AF1_TIM2}, {TIM4,TIM_CHANNEL_3,GPIO_AF2_TIM4}, {TIM10,TIM_CHANNEL_1,GPIO_AF3_TIM10}, {nullptr,0,0}}, {{nullptr,0,NONE}}            },
    { "PB_9",  GPIOB, GPIO_PIN_9,  {{TIM2,TIM_CHANNEL_2,GPIO_AF1_TIM2}, {TIM4,TIM_CHANNEL_4,GPIO_AF2_TIM4}, {TIM11,TIM_CHANNEL_1,GPIO_AF3_TIM11}, {nullptr,0,0}}, {{nullptr,0,NONE}}            },
    { "PB_10", GPIOB, GPIO_PIN_10, {{TIM2,TIM_CHANNEL_3,GPIO_AF1_TIM2}, {nullptr,0,0}},                                                                           {{USART3,GPIO_AF7_USART3,TX}} },
    { "PB_12", GPIOB, GPIO_PIN_12, {{nullptr,0,0}},                                                                                                               {{nullptr,0,NONE}}            },
    { "PB_13", GPIOB, GPIO_PIN_13, {{TIM1,TIM_CHANNEL_1,GPIO_AF1_TIM1}, {nullptr,0,0}},                                                                           {{nullptr,0,NONE}}            },
    { "PB_14", GPIOB, GPIO_PIN_14, {{TIM1,TIM_CHANNEL_2,GPIO_AF1_TIM1}, {TIM8,TIM_CHANNEL_2,GPIO_AF3_TIM8}, {TIM12,TIM_CHANNEL_1,GPIO_AF9_TIM12}, {nullptr,0,0}}, {{nullptr,0,NONE}}            },
    { "PB_15", GPIOB, GPIO_PIN_15, {{TIM1,TIM_CHANNEL_3,GPIO_AF1_TIM1}, {TIM8,TIM_CHANNEL_3,GPIO_AF3_TIM8}, {TIM12,TIM_CHANNEL_2,GPIO_AF9_TIM12}, {nullptr,0,0}}, {{nullptr,0,NONE}}            },

    // -------- Port C --------
    { "PC_0",  GPIOC, GPIO_PIN_0,  {{nullptr,0,0}},                                                                         {{nullptr,0,NONE}}                                       },
    { "PC_1",  GPIOC, GPIO_PIN_1,  {{nullptr,0,0}},                                                                         {{nullptr,0,NONE}}                                       },
    { "PC_2",  GPIOC, GPIO_PIN_2,  {{nullptr,0,0}},                                                                         {{nullptr,0,NONE}}                                       },
    { "PC_3",  GPIOC, GPIO_PIN_3,  {{nullptr,0,0}},                                                                         {{nullptr,0,NONE}}                                       },
    { "PC_4",  GPIOC, GPIO_PIN_4,  {{nullptr,0,0}},                                                                         {{nullptr,0,NONE}}                                       },
    { "PC_5",  GPIOC, GPIO_PIN_5,  {{nullptr,0,0}},                                                                         {{USART3,GPIO_AF7_USART3,RX}, {nullptr,0,NONE}}          },
    { "PC_6",  GPIOC, GPIO_PIN_6,  {{TIM3,TIM_CHANNEL_1,GPIO_AF2_TIM3}, {TIM8,TIM_CHANNEL_1,GPIO_AF3_TIM8}, {nullptr,0,0}}, {{USART6,GPIO_AF8_USART6,TX}, {nullptr,0,NONE}}          },
    { "PC_7",  GPIOC, GPIO_PIN_7,  {{TIM3,TIM_CHANNEL_2,GPIO_AF2_TIM3}, {TIM8,TIM_CHANNEL_2,GPIO_AF3_TIM8}, {nullptr,0,0}}, {{USART6,GPIO_AF8_USART6,RX}, {nullptr,0,NONE}}          },
    { "PC_8",  GPIOC, GPIO_PIN_8,  {{TIM3,TIM_CHANNEL_3,GPIO_AF2_TIM3}, {TIM8,TIM_CHANNEL_3,GPIO_AF3_TIM8}, {nullptr,0,0}}, {{nullptr,0,NONE}}                                       },
    { "PC_9",  GPIOC, GPIO_PIN_9,  {{TIM3,TIM_CHANNEL_4,GPIO_AF2_TIM3}, {TIM8,TIM_CHANNEL_4,GPIO_AF3_TIM8}, {nullptr,0,0}}, {{nullptr,0,NONE}}                                       },
    { "PC_10", GPIOC, GPIO_PIN_10, {{nullptr,0,0}},                                                                         {{USART3,GPIO_AF7_USART3,TX}, {UART4,GPIO_AF8_UART4,TX}} },
    { "PC_11", GPIOC, GPIO_PIN_11, {{nullptr,0,0}},                                                                         {{USART3,GPIO_AF7_USART3,RX}, {UART4,GPIO_AF8_UART4,RX}} },
    { "PC_12", GPIOC, GPIO_PIN_12, {{nullptr,0,0}},                                                                         {{UART5,GPIO_AF8_UART5,TX}, {nullptr,0,NONE}}            },
    { "PC_13", GPIOC, GPIO_PIN_13, {{nullptr,0,0}},                                                                         {{nullptr,0,NONE}}                                       },
    { "PC_14", GPIOC, GPIO_PIN_14, {{nullptr,0,0}},                                                                         {{nullptr,0,NONE}}                                       },
    { "PC_15", GPIOC, GPIO_PIN_15, {{nullptr,0,0}},                                                                         {{nullptr,0,NONE}}                                       },

    // -------- Port D --------
    { "PD_2", GPIOD, GPIO_PIN_2, {{nullptr,0,0}}, {{UART5,GPIO_AF8_UART5,RX}} }
};