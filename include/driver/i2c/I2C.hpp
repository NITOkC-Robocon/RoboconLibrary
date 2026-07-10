#pragma once

#include "core/PinMap.hpp"

#define I2C_BUFFER_SIZE 128


class I2C
{
private:
    PinInfo sdaInfo;
    PinInfo sclInfo;

    I2C_TypeDef* instance = nullptr;

    uint32_t sda_af;
    uint32_t scl_af;

    uint32_t frequency_hz = 100000;

    mutable bool initialized = false;
    void class_initialized();

    void GPIO_Init();
    void init_i2c();

public:
    I2C(PinName sda, PinName scl);

    int write(int address, const char* data, int length, bool repeated = false);
    int read(int address, char* data, int length, bool repeated = false);

    void frequency(uint32_t hz);

    I2C_HandleTypeDef hi2c;
};