#include "WiFiManager.h"

void WiFiManager::connect(const char *ssid, const char *pass)
{
    Serial.println("");
    Serial.println("ESTAMOS CONECTANDO...");

    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("=== ESTEMOS CONECTADO ===");

    Serial.println(
        "IP: " + WiFi.localIP().toString());
    Serial.println(
        "Chip ID: " + String(ESP.getChipId()));
    Serial.println(
        "CPU: " + String(ESP.getCpuFreqMHz()) + " MHz");
    Serial.println(
        "Heap libre: " + String(ESP.getFreeHeap()));
}