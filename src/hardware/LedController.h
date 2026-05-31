#pragma once 

#include <Arduino.h>

class LedController
{
    private:
        uint8_t pin;

    public:
        LedController(uint8_t pin);

        void begin();
        void on();
        void off();
        bool isOn();
};