#include <Arduino.h>
#include <Wire.h>
#include "bumpers.hpp"
#include "buzzer.hpp"
#include "dels.hpp"
#include "i2c.hpp"
#include "roues.hpp"
#include "telecommande.hpp"
#include "ultrason.hpp"

const float INITIAL_SPEED = 50;
const long ONE_SECOND = 1000;
float speed;
long time_of_last_obstacle;

float clampSpeed(float speed)
{
    const float MAX_SPEED = 100, MIN_SPEED = 0;
    return min(max(MIN_SPEED, speed), MAX_SPEED);
}

void setup()
{
    Serial.begin(115200);
    speed = INITIAL_SPEED;
    time_of_last_obstacle = 0;
    initI2C();
    initBumpers();
    initBuzzer();
    initDels();
    initRoues();
    initTelecommande();
    initUltrason();
}

void loop()
{
    auto command = getCodeRecu();
    if (command != -1)
    {
        auto cmd_name = obtenirBoutonNom((REMOTE_BUTTON_CODES)command);
        Serial.println("command received:" + cmd_name);
    }
    auto now = millis();
    switch (command)
    {
    case VOL_PLUS:
        speed = clampSpeed(speed + 1);
        break;
    case VOL_MINUS:
        speed = clampSpeed(speed - 1);
        break;
    case EQUALIZER:
        speed = INITIAL_SPEED;
    default:
        break;
    }
    Serial.println(speed);
    switch (command)
    {
    case N_2:
        /* avancer */
        Serial.println(speed);
        tourner(speed, speed);
        break;
    case N_4:
        /* droite */
        tourner(-speed, speed);
        break;
    case N_6:
        /* gauche */
        tourner(speed, -speed);
        break;
    case N_8:
        /* arriere */
        tourner(-speed, -speed);
        break;
    case N_5:
        /*stop*/
        tourner(0, 0);
        break;
    case N_1: /*rouge*/
        changerCouleur(255, 0, 0);
        break;
    case N_3: /*bleu*/
        changerCouleur(0, 0, 255);
        break;
    case N_7: /*vert*/
        changerCouleur(0, 255, 0);
        break;
    case N_9: /*blanc*/
        changerCouleur(255, 255, 255);
        break;
    default:
        break;
    }
    if (now % 100 == 0)
    {
        auto distance = getDistance();
        // Serial.println("Distance: " + String(distance));
    }
    if (
        detecterObstacle() &&
        (now - time_of_last_obstacle) > (ONE_SECOND * 0.4) // ca fait une demie secondes que le buzzer a sonné.
    )
    {
        // give delay before next time it gets triggered
        time_of_last_obstacle = now;
        tourner(0, 0);
        alumerBuzzer();
        delay(ONE_SECOND * 0.01);
        eteindreBuzzer();
    }
}
