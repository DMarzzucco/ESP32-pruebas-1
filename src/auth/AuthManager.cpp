#include "AuthManager.h"

AuthManager::AuthManager(
    const String &key)
    : key(key),
      authenticated(false),
      attempts(0)
{
}

bool AuthManager::authenticate(
    const String &input)
{
    if (input == key)
    {
        authenticated = true;

        attempts = 0;

        return true;
    }

    attempts++;

    return false;
}

bool AuthManager::isAuthenticated()
{
    return authenticated;
}

int AuthManager::getAttempts()
{
    return attempts;
}

void AuthManager::reset()
{
    authenticated = false;

    attempts = 0;
}