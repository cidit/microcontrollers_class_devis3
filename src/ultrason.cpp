#include "ultrason.hpp"
#include <Arduino.h>

const auto ECHO_PIN = 2, TRIGGER_PIN = 3;

void initUltrason()
{
    pinMode(ECHO_PIN, INPUT);
    pinMode(TRIGGER_PIN, OUTPUT);
}

float getDistance()
{
    // implementation basée sur le code des examples d'alphabot.
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    float cm_dist = pulseIn(ECHO_PIN, HIGH) / 58;
    if (cm_dist > 2 && cm_dist < 400) {
        return cm_dist*10; // millimetres
    } else {
        return -1;
    }
}