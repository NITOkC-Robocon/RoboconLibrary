#include "core/PinMap.hpp"

const PinInfo PinMap[PIN_MAX] = {

    // -------- Port A --------
    { "PA_0",  GPIOA, GPIO_PIN_0,  {TIM2,nullptr},    {TIM_CHANNEL_1,0},             {GPIO_AF1_TIM2,0},              1, {UART4,nullptr},   {GPIO_AF8_UART4,0},  1 },
    { "PA_1",  GPIOA, GPIO_PIN_1,  {TIM2,nullptr},    {TIM_CHANNEL_2,0},             {GPIO_AF1_TIM2,0},              1, {UART4,nullptr},   {GPIO_AF8_UART4,0},  1 },
    { "PA_2",  GPIOA, GPIO_PIN_2,  {TIM2,TIM5},       {TIM_CHANNEL_3,TIM_CHANNEL_3}, {GPIO_AF1_TIM2,GPIO_AF2_TIM5},  2, {USART2,nullptr},  {GPIO_AF7_USART2,0}, 1 },
    { "PA_3",  GPIOA, GPIO_PIN_3,  {TIM2,TIM5},       {TIM_CHANNEL_4,TIM_CHANNEL_4}, {GPIO_AF1_TIM2,GPIO_AF2_TIM5},  2, {USART2,nullptr},  {GPIO_AF7_USART2,0}, 1 },
    { "PA_4",  GPIOA, GPIO_PIN_4,  {TIM2,nullptr},    {TIM_CHANNEL_1,0},             {GPIO_AF1_TIM2,0},              1, {nullptr,nullptr}, {0,0},               0 },
    { "PA_5",  GPIOA, GPIO_PIN_5,  {TIM2,nullptr},    {TIM_CHANNEL_2,0},             {GPIO_AF1_TIM2,0},              1, {nullptr,nullptr}, {0,0},               0 },
    { "PA_6",  GPIOA, GPIO_PIN_6,  {TIM3,TIM13},      {TIM_CHANNEL_1,TIM_CHANNEL_1}, {GPIO_AF2_TIM3,GPIO_AF9_TIM13}, 2, {nullptr,nullptr}, {0,0},               0 },
    { "PA_7",  GPIOA, GPIO_PIN_7,  {TIM3,TIM14},      {TIM_CHANNEL_2,TIM_CHANNEL_1}, {GPIO_AF2_TIM3,GPIO_AF9_TIM14}, 2, {nullptr,nullptr}, {0,0},               0 },
    { "PA_8",  GPIOA, GPIO_PIN_8,  {TIM1,nullptr},    {TIM_CHANNEL_1,0},             {GPIO_AF1_TIM1,0},              1, {nullptr,nullptr}, {0,0},               0 },
    { "PA_9",  GPIOA, GPIO_PIN_9,  {TIM1,nullptr},    {TIM_CHANNEL_2,0},             {GPIO_AF1_TIM1,0},              1, {USART1,nullptr},  {GPIO_AF7_USART1,0}, 1 },
    { "PA_10", GPIOA, GPIO_PIN_10, {TIM1,nullptr},    {TIM_CHANNEL_3,0},             {GPIO_AF1_TIM1,0},              1, {USART1,nullptr},  {GPIO_AF7_USART1,0}, 1 },
    { "PA_13", GPIOA, GPIO_PIN_13, {nullptr,nullptr}, {0,0},                         {0,0},                          0, {nullptr,nullptr}, {0,0},               0 },
    { "PA_14", GPIOA, GPIO_PIN_14, {nullptr,nullptr}, {0,0},                         {0,0},                          0, {nullptr,nullptr}, {0,0},               0 },
    { "PA_15", GPIOA, GPIO_PIN_15, {TIM2,nullptr},    {TIM_CHANNEL_1,0},             {GPIO_AF1_TIM2,0},              1, {nullptr,nullptr}, {0,0},               0 },

    // -------- Port B --------
    { "PB_0",  GPIOB, GPIO_PIN_0,  {TIM3,TIM9},       {TIM_CHANNEL_3,TIM_CHANNEL_3}, {GPIO_AF2_TIM3,GPIO_AF3_TIM9},  2, {nullptr,nullptr}, {0,0},               0 },
    { "PB_1",  GPIOB, GPIO_PIN_1,  {TIM3,TIM9},       {TIM_CHANNEL_4,TIM_CHANNEL_4}, {GPIO_AF2_TIM3,GPIO_AF3_TIM9},  2, {nullptr,nullptr}, {0,0},               0 },
    { "PB_2",  GPIOB, GPIO_PIN_2,  {TIM3,nullptr},    {TIM_CHANNEL_3,0},             {GPIO_AF2_TIM3,0},              1, {nullptr,nullptr}, {0,0},               0 },
    { "PB_3",  GPIOB, GPIO_PIN_3,  {TIM2,TIM3},       {TIM_CHANNEL_2,TIM_CHANNEL_1}, {GPIO_AF1_TIM2,GPIO_AF2_TIM3},  2, {nullptr,nullptr}, {0,0},               0 },
    { "PB_4",  GPIOB, GPIO_PIN_4,  {TIM3,nullptr},    {TIM_CHANNEL_1,0},             {GPIO_AF2_TIM3,0},              1, {nullptr,nullptr}, {0,0},               0 },
    { "PB_5",  GPIOB, GPIO_PIN_5,  {TIM3,nullptr},    {TIM_CHANNEL_2,0},             {GPIO_AF2_TIM3,0},              1, {nullptr,nullptr}, {0,0},               0 },
    { "PB_6",  GPIOB, GPIO_PIN_6,  {TIM4,nullptr},    {TIM_CHANNEL_1,0},             {GPIO_AF2_TIM4,0},              1, {USART1,nullptr},  {GPIO_AF7_USART1,0}, 1 },
    { "PB_7",  GPIOB, GPIO_PIN_7,  {TIM4,nullptr},    {TIM_CHANNEL_2,0},             {GPIO_AF2_TIM4,0},              1, {USART1,nullptr},  {GPIO_AF7_USART1,0}, 1 },
    { "PB_8",  GPIOB, GPIO_PIN_8,  {TIM4,nullptr},    {TIM_CHANNEL_3,0},             {GPIO_AF2_TIM4,0},              1, {nullptr,nullptr}, {0,0},               0 },
    { "PB_9",  GPIOB, GPIO_PIN_9,  {TIM4,nullptr},    {TIM_CHANNEL_4,0},             {GPIO_AF2_TIM4,0},              1, {nullptr,nullptr}, {0,0},               0 },
    { "PB_10", GPIOB, GPIO_PIN_10, {TIM2,nullptr},    {TIM_CHANNEL_3,0},             {GPIO_AF1_TIM2,0},              1, {USART3,nullptr},  {GPIO_AF7_USART3,0}, 1 },
    { "PB_12", GPIOB, GPIO_PIN_12, {nullptr,nullptr}, {0,0},                         {0,0},                          0, {nullptr,nullptr}, {0,0},               0 },
    { "PB_13", GPIOB, GPIO_PIN_13, {nullptr,nullptr}, {0,0},                         {0,0},                          0, {nullptr,nullptr}, {0,0},               0 },
    { "PB_14", GPIOB, GPIO_PIN_14, {nullptr,nullptr}, {0,0},                         {0,0},                          0, {nullptr,nullptr}, {0,0},               0 },
    { "PB_15", GPIOB, GPIO_PIN_15, {nullptr,nullptr}, {0,0},                         {0,0},                          0, {nullptr,nullptr}, {0,0},               0 },

    // -------- Port C --------
    { "PC_0",  GPIOC, GPIO_PIN_0,  {nullptr,nullptr}, {0,0},                         {0,0},                         0, {nullptr,nullptr}, {0,0},               0 },
    { "PC_1",  GPIOC, GPIO_PIN_1,  {nullptr,nullptr}, {0,0},                         {0,0},                         0, {nullptr,nullptr}, {0,0},               0 },
    { "PC_2",  GPIOC, GPIO_PIN_2,  {nullptr,nullptr}, {0,0},                         {0,0},                         0, {nullptr,nullptr}, {0,0},               0 },
    { "PC_3",  GPIOC, GPIO_PIN_3,  {nullptr,nullptr}, {0,0},                         {0,0},                         0, {nullptr,nullptr}, {0,0},               0 },
    { "PC_4",  GPIOC, GPIO_PIN_4,  {nullptr,nullptr}, {0,0},                         {0,0},                         0, {nullptr,nullptr}, {0,0},               0 },
    { "PC_5",  GPIOC, GPIO_PIN_5,  {nullptr,nullptr}, {0,0},                         {0,0},                         0, {nullptr,nullptr}, {0,0},               0 },
    { "PC_6",  GPIOC, GPIO_PIN_6,  {TIM3,TIM8},       {TIM_CHANNEL_1,TIM_CHANNEL_1}, {GPIO_AF3_TIM8,GPIO_AF3_TIM8}, 2, {USART6,nullptr},  {GPIO_AF8_USART6,0}, 1 },
    { "PC_7",  GPIOC, GPIO_PIN_7,  {TIM3,TIM8},       {TIM_CHANNEL_2,TIM_CHANNEL_2}, {GPIO_AF2_TIM3,GPIO_AF3_TIM8}, 2, {USART6,nullptr},  {GPIO_AF8_USART6,0}, 1 },
    { "PC_8",  GPIOC, GPIO_PIN_8,  {TIM8,nullptr},    {TIM_CHANNEL_3,0},             {GPIO_AF3_TIM8,0},             1, {nullptr,nullptr}, {0,0},               0 },
    { "PC_9",  GPIOC, GPIO_PIN_9,  {TIM3,TIM8},       {TIM_CHANNEL_4,TIM_CHANNEL_4}, {GPIO_AF2_TIM3,GPIO_AF3_TIM8}, 2, {USART3,nullptr},  {GPIO_AF7_USART3,0}, 1 },
    { "PC_10", GPIOC, GPIO_PIN_10, {TIM3,nullptr},    {TIM_CHANNEL_3,0},             {GPIO_AF2_TIM3,0},             1, {UART4,nullptr},   {GPIO_AF8_UART4,0},  1 },
    { "PC_11", GPIOC, GPIO_PIN_11, {TIM3,nullptr},    {TIM_CHANNEL_4,0},             {GPIO_AF2_TIM3,0},             1, {UART4,nullptr},   {GPIO_AF8_UART4,0},  1 },
    { "PC_12", GPIOC, GPIO_PIN_12, {nullptr,nullptr}, {0,0},                         {0,0},                         0, {UART5,nullptr},   {GPIO_AF8_UART5,0},  1 },
    { "PC_13", GPIOC, GPIO_PIN_13, {nullptr,nullptr}, {0,0},                         {0,0},                         0, {nullptr,nullptr}, {0,0},               0 },
    { "PC_14", GPIOC, GPIO_PIN_14, {nullptr,nullptr}, {0,0},                         {0,0},                         0, {nullptr,nullptr}, {0,0},               0 },
    { "PC_15", GPIOC, GPIO_PIN_15, {nullptr,nullptr}, {0,0},                         {0,0},                         0, {nullptr,nullptr}, {0,0},               0 },

    // -------- Port D --------
    { "PD_2", GPIOD, GPIO_PIN_2, {nullptr,nullptr}, {0,0}, {0,0}, 0, {UART5,nullptr}, {GPIO_AF8_UART5,0}, 1 },
};