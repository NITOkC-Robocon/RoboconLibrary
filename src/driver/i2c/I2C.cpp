#include "driver/i2c/I2C.hpp"
#include "core/System.hpp"
#include "core/I2C_Init.hpp"



I2C::I2C(PinName sda, PinName scl)
{
    sdaInfo = PinMap[sda];
    sclInfo = PinMap[scl];

    if (sdaInfo.i2c_info[0].i2c != sclInfo.i2c_info[0].i2c)
    {
        // エラー（ここ重要）
        while (1);
    }

    instance = sdaInfo.i2c_info[0].i2c;
    sda_af = sdaInfo.i2c_info[0].af;
    scl_af = sclInfo.i2c_info[0].af;
}

void I2C::class_initialized()
{
    if (initialized) return;
    initialized = true;

    MCU_Init();

    GPIO_Init();
    init_i2c();
}

void I2C::GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    enableGpioClock(sdaInfo.port);
    enableGpioClock(sclInfo.port);

    // SDAピンの初期化
    GPIO_InitStruct.Pin = sdaInfo.pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ;
    GPIO_InitStruct.Alternate = sda_af;
    HAL_GPIO_Init(sdaInfo.port, &GPIO_InitStruct);

    // SCLピンの初期化
    GPIO_InitStruct.Pin = sclInfo.pin;
    GPIO_InitStruct.Alternate = scl_af;
    HAL_GPIO_Init(sclInfo.port, &GPIO_InitStruct);
}

void I2C::init_i2c()
{
    enableI2CClock(instance);

    hi2c.Instance = instance;

    I2C_SetTiming(&hi2c, frequency_hz);
    hi2c.Init.OwnAddress1 = 0;
    hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c.Init.OwnAddress2 = 0;
    hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    HAL_I2C_Init(&hi2c);
}

int I2C::write(int address, const char* data, int length, bool repeated)
{
    class_initialized();

    if (HAL_I2C_Master_Transmit(
            &hi2c,
            address,
            (uint8_t*)data,
            length,
            100) == HAL_OK)
        return length;

    return -1;
}

int I2C::read(int address, char* data, int length, bool repeated)
{
    class_initialized();

    if (HAL_I2C_Master_Receive(
            &hi2c,
            address,
            (uint8_t*)data,
            length,
            100) == HAL_OK)
        return length;

    return -1;
}

void I2C::frequency(I2C_freq mode)
{
    class_initialized();

    frequency_hz = static_cast<uint32_t>(mode);
    if (initialized)
        init_i2c();
}