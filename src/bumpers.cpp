#include "bumpers.hpp"
#include "i2c.hpp"

/**
 * Détecte si un obstacle se fait détecter par les pare-choc.
 * Code emprunté de l'exemple `Infrared-Obstacle-Avoidance`.
 * Je suis pas super sur de comprendre ce code, mais je sais au moins l'utiliser.
 *
 * @returns `true` si un obstacle a été détecté, `false` si non.
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