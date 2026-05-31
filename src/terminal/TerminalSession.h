#pragma once

#include <ESP8266WiFi.h>

#include "../auth/AuthManager.h"
#include "../commands/CommandHandler.h"

class TerminalSession
{
private:
    WiFiServer server;

    WiFiClient client;

    AuthManager &auth;

    CommandHandler &commands;

    unsigned long timeoutMs;

    unsigned long lastActivity;

    void handleConnection();

    void handleTimeout();

    void handleAuth(
        const String &input);

public:
    TerminalSession(
        uint16_t port,
        unsigned long timeoutMs,
        AuthManager &auth,
        CommandHandler &commands);

    void begin();

    void update();
};