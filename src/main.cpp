#include <Arduino.h>

#include "auth/AuthManager.h"
#include "commands/CommandHandler.h"
#include "config/Config.h"
#include "hardware/LedController.h"
#include "terminal/TerminalSession.h"
#include "wifi/WiFiManager.h"

LedController led(LED_PIN);
AuthManager auth(key);
CommandHandler commands(led);
TerminalSession terminalSession(23, TIMEOUT, auth, commands);
WiFiManager wifi;

void setup()
{
  Serial.begin(115200);

  led.begin();

  wifi.connect(ssid, pass);

  terminalSession.begin();
}

void loop()
{
  terminalSession.update();
}