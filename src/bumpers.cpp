#include "bumpers.hpp"
#include "i2c.hpp"

/**
 *
 */
bool detecterObstacle()
{
    int value;
    bool success = lire(value);
    if (!success)
    {
        return false;
    }
    ecrire(0xC0 | value);  // set Pin High
    success = lire(value); // read Pin
    if (!success)
    {
        return false;
    }
    return (value | 0x3F) != 0xFF;
}