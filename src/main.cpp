#include <ESP8266WiFi.h>

const char *ssid = "HITRON-0420";
const char *pass = "W78U39EPKDQ7";

WiFiServer server(23);

WiFiClient client;

#define LED D4

const String key = "123";

int intentos = 0;

bool auth = false;

void setup()
{

  Serial.begin(115200);

  pinMode(LED, OUTPUT);

  digitalWrite(LED, HIGH);

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

  server.begin();

  Serial.println("SERVER INICIADO");
}

void loop()
{

  if (server.hasClient())
  {

    client = server.accept();

    auth = false;

    client.println("=== AGREGA LA CONTRA ===");
    client.println("Cucha, si le erras tres veces, cagaste.");
    client.println("Ingresa la clave de seguridad:");
  }

  if (client && client.connected() && client.available())
  {

    String comando = client.readStringUntil('\n');

    comando.trim();

    if (!auth)
    {

      if (comando == key)
      {

        auth = true;

        intentos = 0;

        client.println("WILKOMEN");
        client.println("Comandos: on, off, status, exit");
        client.print("> ");
      }
      else
      {
        intentos++;
        if (intentos >= 3)
        {
          client.println("La cagaste tres veces, nos vimos en narnia");
          intentos = 0;
          client.stop();
        }
        client.println("Clave incorrecta, intenta de nuevo");
        client.println("Intentos restantes: " + String(3 - intentos));
        if (intentos < 3) {
          client.println("TU ULTIMO INTENTO, NO LA CAGUES");
        }
        client.println("Ingresa la clave de seguridad:");
      }

      return;
    }

    if (comando == "on")
    {

      digitalWrite(LED, LOW);

      client.println("PRENDIO");
    }

    else if (comando == "off")
    {

      digitalWrite(LED, HIGH);

      client.println("APAGO");
    }

    else if (comando == "status")
    {

      bool prendido = digitalRead(LED) == LOW;

      client.println(prendido ? "Esta prendido" : "Esta apagado");
    }

    else if (comando == "exit")
    {

      client.println("CHAU");

      client.stop();

      return;
    }

    else
    {

      client.println("No existe ese comando");
    }

    client.print("> ");
  }
}