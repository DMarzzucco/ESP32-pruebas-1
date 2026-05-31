#pragma once

#include <ESP8266WiFi.h>

class WiFiManager
{
public:
    void connect(const char *ssid, const char *pass);
};