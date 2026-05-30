#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "HITRON-0420";
const char *pass = "W78U39EPKDQ7";

ESP8266WebServer server(80);

#define LED D4

void handleRoot()
{

  digitalWrite(LED, !digitalRead(LED));

  bool prendido = digitalRead(LED) == LOW;

  if (prendido)
  {
    Serial.println("prendido");
    server.send(200, "text/plain", "prendido");
  }
  else
  {
    Serial.println("apagado");
    server.send(200, "text/plain", "apagado");
  }
}

void setup()
{

  Serial.begin(115200);

  pinMode(LED, OUTPUT);

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP().toString());
  Serial.println("Chip ID: " + String(ESP.getChipId()));
  Serial.println("CPU Frequency: " + String(ESP.getCpuFreqMHz()) + " MHz");

  server.on("/", handleRoot);

  server.begin();
}

void loop()
{
  server.handleClient();
}