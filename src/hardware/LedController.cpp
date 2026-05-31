#include "LedController.h"

LedController::LedController(uint8_t pin) : pin(pin)
{
}

void LedController::begin()
{
    pinMode(pin, OUTPUT);

    off();
}

void LedController::on()
{
    digitalWrite(pin, LOW);
}

void LedController::off()
{
    digitalWrite(pin, HIGH);
}

bool LedController::isOn()
{
    return digitalRead(pin) == LOW;
}