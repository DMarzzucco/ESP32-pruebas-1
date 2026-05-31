#include <ESP8266WiFi.h>

const char *ssid = "HITRON-0420";
const char *pass = "W78U39EPKDQ7";

WiFiServer server(23);
WiFiClient client;

#define LED D4

const String key = "123";

bool auth = false;

int intentos = 0;

unsigned long lastActivity = 0;

const unsigned long TIMEOUT = 60000;

void printPrompt()
{
  client.print("Arre loco> ");
}

void handleHelp()
{
  client.println("=== COMANDOS ===");
  client.println("help     -> Ayuda");
  client.println("on       -> prende el led");
  client.println("off      -> apaga el led");
  client.println("status   -> estado del led");
  client.println("info     -> info del sistema");
  client.println("clear    -> limpia terminal");
  client.println("reboot   -> reinicia ESP");
  client.println("exit     -> cerrar conexion");
}

void handleInfo()
{
  client.println("=== INFO DEL SISTEMA ===");

  client.println("IP: " + WiFi.localIP().toString());

  client.println(
      "Heap libre: " + String(ESP.getFreeHeap()) + " bytes");

  client.println(
      "Chip ID: " + String(ESP.getChipId()));

  client.println(
      "CPU: " + String(ESP.getCpuFreqMHz()) + " MHz");

  client.println(
      "RSSI: " + String(WiFi.RSSI()) + " dBm");
}

void clearTerminal()
{
  client.write(27);
  client.print("[2J");

  client.write(27);
  client.print("[H");
}

void handleCommand(String comando)
{
  if (comando == "help")
  {
    handleHelp();
  }

  else if (comando == "on")
  {
    digitalWrite(LED, LOW);

    client.println("Se prendio una luz en tu vida");
  }

  else if (comando == "off")
  {
    digitalWrite(LED, HIGH);

    client.println("Apagaste la unica esperenza de tu existencia");
  }

  else if (comando == "status")
  {
    bool prendido = digitalRead(LED) == LOW;

    client.println(
        prendido ? "Esta prendido, por ahora" : "Prende la luz, no veo un choto.");
  }

  else if (comando == "info")
  {
    handleInfo();
  }

  else if (comando == "clear")
  {
    clearTerminal();
  }

  else if (comando == "reboot")
  {
    client.println("Banca que estoy reiniciando...");

    delay(1000);

    ESP.restart();
  }

  else if (comando == "exit")
  {
    client.println("Cuidate, no hagas cagada.");

    client.stop();

    return;
  }

  else if (comando == "ping")
  {
    client.println("tu vieja");
  }

  else
  {
    client.println("No existe ese comando, pete. Si necesitas ayuda, escribe 'help'");
  }

  printPrompt();
}

void handleAuth(String comando)
{
  if (comando == key)
  {
    auth = true;

    intentos = 0;

    client.println("");
    client.println("=== BIEN AHEEE ===");

    handleHelp();

    printPrompt();
  }

  else
  {
    intentos++;

    if (intentos >= 4)
    {
      client.println("");
      client.println("Pero sos boludo, mira que te dije que tenias un solo intento.");

      client.stop();

      intentos = 0;

      return;
    }

    client.println("");
    client.println("Esa no es la clave");

    if (intentos < 3)
    {
      client.println(
          "te quedan " + String(3 - intentos) + " intentos");
    }
    else if (intentos == 3)
    {
      client.println("NO LA CAGUES");
      client.println("Te queda un solo intento. Si la cagas en esta fuiste.");
    }

    client.println("ingresa la clave:");
  }
}

void handleConnection()
{
  if (server.hasClient())
  {
    if (client && client.connected())
    {
      client.println("Otro salame se intento conectar");
      client.stop();
    }

    client = server.accept();

    auth = false;

    intentos = 0;

    lastActivity = millis();

    Serial.println("");
    Serial.println(
        "La ip del cliente: " +
        client.remoteIP().toString());

    client.println("");
    client.println("================================");
    client.println(" EL AHRRE LOCO v1.0");
    client.println("================================");
    client.println("");
    client.println("Mete la clave:");
  }
}

void handleTimeout()
{
  if (
      client &&
      client.connected() &&
      millis() - lastActivity > TIMEOUT)
  {
    client.println("");
    client.println("Se termino el tiempo de conexion papa, nos vimos");

    client.stop();

    Serial.println("Cliente desconectado por timeout");
  }
}

void setup()
{
  Serial.begin(115200);

  pinMode(LED, OUTPUT);

  digitalWrite(LED, HIGH);

  Serial.println("");
  Serial.println("Conectandododododo");

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
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

  server.begin();

  Serial.println("");
  Serial.println("Server iniciado");
}

void loop()
{
  handleConnection();

  handleTimeout();

  if (
      client &&
      client.connected() &&
      client.available())
  {
    lastActivity = millis();

    String comando =
        client.readStringUntil('\n');

    comando.trim();

    if (!auth)
    {
      handleAuth(comando);

      return;
    }

    handleCommand(comando);
  }
}