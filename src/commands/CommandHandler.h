#pragma once

#include <ESP8266WiFi.h>

#include "../hardware/LedController.h"

class CommandHandler
{
private:
    LedController &led;

    void clearTerminal(
        WiFiClient &client);

    void handleInfo(
        WiFiClient &client);

    void handleHelp(
        WiFiClient &client);

public:
    CommandHandler(
        LedController &led);

    bool handle(
        WiFiClient &client,
        const String &command);

    void printPrompt(
        WiFiClient &client);
};