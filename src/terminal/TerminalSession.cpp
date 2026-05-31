#include "TerminalSession.h"

TerminalSession::TerminalSession(
    uint16_t port,
        unsigned long timeoutMs,
    AuthManager &auth,
    CommandHandler &commands)
    : server(port),
    client(),
    auth(auth),
    commands(commands),
            timeoutMs(timeoutMs),
            lastActivity(0)
{
}

void TerminalSession::begin()
{
    server.begin();

    Serial.println("");
    Serial.println("Server iniciado");
}

void TerminalSession::handleConnection()
{
    if (server.hasClient())
    {
        if (client && client.connected())
        {
            client.println(
                "Otro salame se intento conectar");

            client.stop();
        }

        client = server.accept();

        auth.reset();

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

void TerminalSession::handleTimeout()
{
    if (
        client &&
        client.connected() &&
        millis() - lastActivity > timeoutMs)
    {
        client.println("");

        client.println(
            "Se termino el tiempo de conexion papa, nos vimos");

        client.stop();

        Serial.println(
            "Cliente desconectado por timeout");
    }
}

void TerminalSession::handleAuth(
    const String &input)
{
    bool ok =
        auth.authenticate(input);

    if (ok)
    {
        client.println("");
        client.println("=== BIEN AHEEE ===");

        commands.handle(
            client,
            "help");

        commands.printPrompt(client);

        return;
    }

    client.println("");
    client.println("Esa no es la clave");

    int attempts =
        auth.getAttempts();

    if (attempts < 3)
    {
        client.println(
            "te quedan " +
            String(3 - attempts) +
            " intentos");
    }
    else if (attempts == 3)
    {
        client.println("NO LA CAGUES");

        client.println(
            "Te queda un solo intento. Si la cagas en esta fuiste.");
    }

    if (attempts >= 4)
    {
        client.println("");

        client.println(
            "Pero sos boludo, mira que te dije que tenias un solo intento.");

        client.stop();

        auth.reset();

        return;
    }

    client.println("ingresa la clave:");
}

void TerminalSession::update()
{
    handleConnection();

    handleTimeout();

    if (
        client &&
        client.connected() &&
        client.available())
    {
        lastActivity = millis();

        String command =
            client.readStringUntil('\n');

        command.trim();

        if (!auth.isAuthenticated())
        {
            handleAuth(command);

            return;
        }

        commands.handle(
            client,
            command);
    }
}