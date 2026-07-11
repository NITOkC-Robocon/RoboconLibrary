#include <RoboconLibrary.h>

I2C i2c(PB_9, PB_8);
RawSerial pc(USBTX, USBRX);

// AD0=GNDなら0x68、AD0=VCCなら0x69
constexpr uint8_t MPU6050_ADDR = (0x68 << 1);

//---------------------------------
// I2C補助関数
//---------------------------------

bool writeReg(uint8_t reg, uint8_t data)
{
    char buf[2] = {(char)reg, (char)data};
    return i2c.write(MPU6050_ADDR, buf, 2) == 2;
}

bool readRegs(uint8_t reg, char* data, int len)
{
    if(i2c.write(MPU6050_ADDR, (char*)&reg, 1, true) != 1)
        return false;

    return i2c.read(MPU6050_ADDR, data, len) == len;
}

int16_t toInt16(char high, char low)
{
    return (int16_t)(((uint8_t)high << 8) | (uint8_t)low);
}

//---------------------------------

int main()
{
    
    char who = 0;

    // WHO_AM_I確認
    if(readRegs(0x75, &who, 1))
        pc.printf("WHO_AM_I = 0x%02X\r\n", who);
    else
    {
        pc.printf("WHO_AM_I Read Error\r\n");
        while(1);
    }

    // スリープ解除
    writeReg(0x6B, 0x00);
    wait_ms(100);

    while (1)
    {   
        char data[6];

        if(readRegs(0x43, data, 6))
        {
            int16_t gx = toInt16(data[0], data[1]);
            int16_t gy = toInt16(data[2], data[3]);
            int16_t gz = toInt16(data[4], data[5]);

            // ±250dps設定時
            float gx_dps = gx / 131.0f;
            float gy_dps = gy / 131.0f;
            float gz_dps = gz / 131.0f;

            pc.printf(
                "GX:%7.2f  GY:%7.2f  GZ:%7.2f\r\n",
                gx_dps,
                gy_dps,
                gz_dps
            );
        }
        else
        {
            pc.printf("Read Error\r\n");
        }

        
        wait_ms(100);
    }
}