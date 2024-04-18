#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "dels.hpp"

/*
 * Code inspiré de l'exemple `W2812`.
 * Je suis pas super sur de comprendre ce code, mais je sais au moins l'utiliser.
 */

const auto PIN_DELS = 7;
const auto NOMBRE_DE_DELS = 4;

Adafruit_NeoPixel RGB = Adafruit_NeoPixel(NOMBRE_DE_DELS, PIN_DELS, NEO_GRB + NEO_KHZ800);

/**
 * Initialise les dels et le met à blanc par défaut.
 */
void initDels()
{
    RGB.begin();
    changerCouleur(255, 255, 255);
}

/**
 * Change la couleur des dels.
 * @param rouge La quantitée de rouge dans la couleur. [0-255]
 * @param vert La quantitée de vert dans la couleur. [0-255]
 * @param bleu La quantitée de bleu dans la couleur. [0-255]
 */
void changerCouleur(uint8_t rouge, uint8_t vert, uint8_t bleu)
{
    auto color = Adafruit_NeoPixel::Color(rouge, vert, bleu);
    for (auto i = 0; i < NOMBRE_DE_DELS; i++)
    {
        RGB.setPixelColor(i, color);
    }
    RGB.show();
}
