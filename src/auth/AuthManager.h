#pragma once

#include <Arduino.h>

class AuthManager
{
private:
    String key;

    bool authenticated;

    int attempts;

public:
    AuthManager(const String &key);

    bool authenticate(const String &input);

    bool isAuthenticated();

    int getAttempts();

    void reset();
};