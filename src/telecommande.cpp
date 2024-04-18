#include "telecommande.hpp"
#include <Arduino.h>
#include <IRremote.h>

const auto RECEIVER_PIN = 4;

/**
 * Traduit un code de télécommande en le nom du bouton qui lui est associé.
 * Principalement utile pour afficher le code sans à avoir à se rappler de son chiffre.
 * @param code Le code de télécommande à nommer.
 * @return Le nom du code donné en paramètres.
 */
String obtenirBoutonNom(REMOTE_BUTTON_CODES code)
{
    switch (code)
    {
    case CHANEL_MINUS:
        return "CHANEL_MINUS";
    case CHANNEL:
        return "CHANNEL ";
    case CHANEL_PLUS:
        return "CHANEL_PLUS ";
    case PREV:
        return "PREV";
    case NEXT:
        return "NEXT";
    case PLAY_PAUSE:
        return "PLAY_PAUSE";
    case VOL_MINUS:
        return "VOL_MINUS";
    case VOL_PLUS:
        return "VOL_PLUS";
    case EQUALIZER:
        return "EQUALIZER";
    case N_0:
        return "N_0";
    case N_100_PLUS:
        return "N_100_PLUS";
    case N_200_PLUS:
        return "N_200_PLUS";
    case N_1:
        return "N_1";
    case N_2:
        return "N_2";
    case N_3:
        return "N_3";
    case N_4:
        return "N_4";
    case N_5:
        return "N_5";
    case N_6:
        return "N_6";
    case N_7:
        return "N_7";
    case N_8:
        return "N_8";
    case N_9:
        return "N_9";
    default:
        return "INVALID_CODE";
    };
}

/**
 * Initialise le receveur infrarouge pour capter les signaux de la télécommande.
 */
void initTelecommande()
{
    IrReceiver.begin(RECEIVER_PIN);
}

/**
 * Sert à déterminer si le capteur infrarouge a capté une commande.
 * @return le code reçu, ou -1 si aucun code n'a été décodé.
 */
long getCodeRecu()
{
    if (!IrReceiver.decode())
    {
        return -1;
    }
    auto code = IrReceiver.decodedIRData.command;
    IrReceiver.resume();
    return code;
}