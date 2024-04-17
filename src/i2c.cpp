#include "i2c.hpp"
#include <Arduino.h>
#include <Wire.h>

const auto I2C_ADDR = 0x20;

void initI2C()
{
    Wire.begin();
}

void ecrire(int data)
{
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(data);
    Wire.endTransmission();
}

bool lire(int &out)
{
    int data = -1;
    Wire.requestFrom(I2C_ADDR, 1);
    if (!Wire.available())
    {
        return false;
    }
    out = Wire.read();
    return true;
}