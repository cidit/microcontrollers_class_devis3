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

/**
 * Assure une vitesse dans l'étendue attendue.
 * @param speed Une vitesse de taille arbitraire.
 * @return La vitesse passée en paramètres, mais limitée à l'étendue [0-100].
 */
float clampSpeed(float speed)
{
    const float MAX_SPEED = 100, MIN_SPEED = 0;
    return min(max(MIN_SPEED, speed), MAX_SPEED);
}

/**
 * Imprime la commande passée en paramètres sur le moniteur série.
 * @param command La commande à imprimer.
*/
void raporterCommande(long command)
{
    auto cmd_name = obtenirBoutonNom((REMOTE_BUTTON_CODES)command);
    Serial.println("command received:" + cmd_name);
}

/**
 * Exécute la commande passée en paramètres.
 * Les contrôles sont listés dans le fichier `README.md`.
 * @param command La commande à exécuter.
*/
void executerCommande(long command)
{
    switch (command)
    {
    case VOL_PLUS:
        // augmenter la vitesse
        speed = clampSpeed(speed + 1);
        break;
    case VOL_MINUS:
        // diminuer la vitesse
        speed = clampSpeed(speed - 1);
        break;
    case EQUALIZER:
        // réinitialiser la vitesse
        speed = INITIAL_SPEED;
        break;
    case N_2:
        // avancer
        Serial.println(speed);
        tourner(speed, speed);
        break;
    case N_4:
        // droite
        tourner(-speed, speed);
        break;
    case N_6:
        // gauche
        tourner(speed, -speed);
        break;
    case N_8:
        // arriere
        tourner(-speed, -speed);
        break;
    case N_5:
        // stop
        tourner(0, 0);
        break;
    case N_1:
        // rouge
        changerCouleur(255, 0, 0);
        break;
    case N_3:
        // bleu
        changerCouleur(0, 0, 255);
        break;
    case N_7:
        // vert
        changerCouleur(0, 255, 0);
        break;
    case N_9:
        // blanc
        changerCouleur(255, 255, 255);
        break;
    default:
        break;
    }
}

/**
 * Imprime la distance sur le moniteur série.
*/
void raporterDistance()
{
    auto distance = getDistance();
    Serial.println("Distance: " + String(distance));
}

/**
 * Émet un très court buzz, juste assez long pour être clairement remarquable mais pas asser pour être carrément chiant et insuportable.
*/
void petitBuzz()
{
    alumerBuzzer();
    delay(ONE_SECOND * 0.01);
    eteindreBuzzer();
}

void setup()
{
    Serial.begin(115200);
    speed = INITIAL_SPEED;
    time_of_last_obstacle = 0;
    initI2C();
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
        raporterCommande(command);
    }

    executerCommande(command);

    auto now = millis();

    if (now % 100 == 0)
    {
        raporterDistance();
    }

    // Déterminer si ç fait assez de temps que le buzzer a sonné.
    auto bumpersEffectTimerExpired = (now - time_of_last_obstacle) > (ONE_SECOND * 0.4);
    if (
        detecterObstacle() && bumpersEffectTimerExpired)
    {
        // Réinitialiser la condition du chronomètre des pare-chocs
        time_of_last_obstacle = now;

        // Arrêter le robot pour éviter qu'il ne se brise;
        tourner(0, 0);

        petitBuzz();
    }
}
