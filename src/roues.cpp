#include <Arduino.h>
#include "roues.hpp"


const motor_pin_set RIGHT_MOTOR{5, A2, A3}, LEFT_MOTOR{6, A0, A1};

void setMotorPinModes(motor_pin_set pins)
{
    pinMode(pins.speed, OUTPUT);
    pinMode(pins.forward, OUTPUT);
    pinMode(pins.backward, OUTPUT);
}

/**
 * @param speed element of [-1, 1]
 */
void setMotorSpeed(motor_pin_set motor_pins, float speed)
{
    auto magnitude = abs(speed);
    auto pwm = magnitude*255;
    if (speed > 0)
    {
        digitalWrite(motor_pins.forward, HIGH);
        digitalWrite(motor_pins.backward, LOW);
        analogWrite(motor_pins.speed, pwm);
    }
    else if (speed < 0)
    {
        digitalWrite(motor_pins.forward, LOW);
        digitalWrite(motor_pins.backward, HIGH);
        analogWrite(motor_pins.speed, pwm);
    }
    else
    {
        digitalWrite(motor_pins.forward, LOW);
        digitalWrite(motor_pins.backward, LOW);
        analogWrite(motor_pins.speed, 0);
    }
}

void initRoues()
{
    setMotorPinModes(RIGHT_MOTOR);
    setMotorPinModes(LEFT_MOTOR);
}

void tourner(float vitesseG, float vitesseD)
{
    auto speedR = vitesseD/100;
    auto speedL = vitesseG/100;
    setMotorSpeed(RIGHT_MOTOR, -speedR);
    setMotorSpeed(LEFT_MOTOR, speedL);
}