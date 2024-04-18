#include "buzzer.hpp"
#include "i2c.hpp"
#include <Arduino.h>

/*
 * Code emprunté de l'exemple `Joystick`.
 * Je suis pas super sur de comprendre ce code, mais je sais au moins l'utiliser.
 */

/**
 * Alumme le buzzer.
 */
void alumerBuzzer()
{
    int value;
    bool success = lire(value);
    if (!success)
    {
        return;
    }
    ecrire(0xDF & value);
}

/**
 * Éteint le buzzer.
 */
void eteindreBuzzer()
{
    int value;
    bool success = lire(value);
    if (!success)
    {
        return;
    }
    ecrire(0x20 | value);
}