#include "CommandHandler.h"

CommandHandler::CommandHandler(
    LedController &led)
    : led(led)
{
}

void CommandHandler::printPrompt(
    WiFiClient &client)
{
    client.print("Arre loco> ");
}

void CommandHandler::handleHelp(
    WiFiClient &client)
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

void CommandHandler::handleInfo(
    WiFiClient &client)
{
    client.println("=== INFO DEL SISTEMA ===");

    client.println(
        "IP: " + WiFi.localIP().toString());

    client.println(
        "Heap libre: " +
        String(ESP.getFreeHeap()) +
        " bytes");

    client.println(
        "Chip ID: " +
        String(ESP.getChipId()));

    client.println(
        "CPU: " +
        String(ESP.getCpuFreqMHz()) +
        " MHz");

    client.println(
        "RSSI: " +
        String(WiFi.RSSI()) +
        " dBm");
}

void CommandHandler::clearTerminal(
    WiFiClient &client)
{
    client.write(27);

    client.print("[2J");

    client.write(27);

    client.print("[H");
}

bool CommandHandler::handle(
    WiFiClient &client,
    const String &command)
{
    if (command == "help")
    {
        handleHelp(client);
    }

    else if (command == "on")
    {
        led.on();

        client.println(
            "Se prendio una luz en tu vida");
    }

    else if (command == "off")
    {
        led.off();

        client.println(
            "Apagaste la unica esperenza de tu existencia");
    }

    else if (command == "status")
    {
        client.println(
            led.isOn()
                ? "Esta prendido, por ahora"
                : "Prende la luz, no veo un choto.");
    }

    else if (command == "info")
    {
        handleInfo(client);
    }

    else if (command == "clear")
    {
        clearTerminal(client);
    }

    else if (command == "reboot")
    {
        client.println(
            "Banca que estoy reiniciando...");

        delay(1000);

        ESP.restart();
    }

    else if (command == "exit")
    {
        client.println(
            "Cuidate, no hagas cagada.");

        client.stop();

        return false;
    }

    else if (command == "ping")
    {
        client.println("tu vieja");
    }

    else
    {
        client.println(
            "No existe ese comando, pete. Si necesitas ayuda, escribe 'help'");
    }

    printPrompt(client);

    return true;
}