#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "dels.hpp"

const auto PIN_DELS =7;
const auto NOMBRE_DE_DELS = 4;

Adafruit_NeoPixel RGB = Adafruit_NeoPixel(NOMBRE_DE_DELS, PIN_DELS, NEO_GRB + NEO_KHZ800);

void initDels()
{
    RGB.begin();
    changerCouleur(255, 255, 255);
}

void changerCouleur(uint8_t rouge, uint8_t vert, uint8_t bleu)
{
    auto color = Adafruit_NeoPixel::Color(rouge, vert, bleu);
    for (auto i = 0; i < NOMBRE_DE_DELS; i++)
    {
        RGB.setPixelColor(i, color);
    }
    RGB.show();
}
