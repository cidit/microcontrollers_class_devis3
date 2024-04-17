#include "buzzer.hpp"
#include "i2c.hpp"
#include <Arduino.h>


void initBuzzer()
{
    // noop
}

void alumerBuzzer()
{
    int value;
    bool success = lire(value);
    if (!success) {
        return;
    }
    ecrire(0xDF & value);
}


void eteindreBuzzer() {
    int value;
    bool success = lire(value);
    if (!success) {
        return;
    }
    ecrire(0x20 | value);
}