#pragma once

#include "core/PinMap.hpp"

#define I2C_BUFFER_SIZE 128


enum class I2C_freq : uint32_t
{
    Standard = 100000,   // 100 kHz
    Fast = 400000,       // 400 kHz
    FastPuls = 1000000,   // 1 MHz
};

/**
 * @brief I2C通信用クラス
 * 
 * クラス定義： 
 * 
 * I2C i2c(SDA_PIN, SCL_PIN); 　//デフォルトでstandard mode(100kHz)で初期化される
 * 
 * <オブジェクト生成例>
 * 
 * I2C i2c(PB_7, PB_6);
 */
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
    /**
     * @brief I2C通信を使うための初期化を行う
     * 
     * SDAピンとSCLピンを指定して、I2Cハードウェアを準備します。
     * 
     * @param sda SDAピン
     * @param scl SCLピン
     */
    I2C(PinName sda, PinName scl);

    /**
     * @brief I2C通信でデータを書き込む
     * 
     * <使用例>
     * 
     * i2c.write(0x50, "Hello", 5);
     * 
     * @param address I2Cデバイスのアドレス
     * @param data 書き込むデータのポインタ
     * @param length 書き込むデータの長さ
     * @param repeated trueの場合、リピートスタートを使用する
     */
    int write(int address, const char* data, int length, bool repeated = false);

    /**
     * @brief I2C通信でデータを読み込む
     * 
     * <使用例>
     * 
     * char buffer[10];
     * i2c.read(0x50, buffer, 10);
     * 
     * @param address I2Cデバイスのアドレス
     * @param data 読み込むデータのポインタ
     * @param length 読み込むデータの長さ
     * @param repeated trueの場合、リピートスタートを使用する
     */
    int read(int address, char* data, int length, bool repeated = false);

    /**
     * @brief I2C通信の周波数を設定する
     * 
     * <使用例>
     * 
     * i2c.frequency(400000); // 400kHzに設定
     * 
     * @param hz 設定する周波数(Hz)
     */
    void frequency(I2C_freq mode);

    I2C_HandleTypeDef hi2c;
};