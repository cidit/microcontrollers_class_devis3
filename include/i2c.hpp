#pragma once
#include <Arduino.h>

/*
 * basé sur le fichier d'example "Infrared-Obstacle-Avoidance.ino"
 */

/**
 *
 */
void initI2C();

/**
 *
 */
void ecrire(int data);

/**
 *
 */
bool lire(int &out);