#include "wifi_manager.h"
#include "config.h"


void WiFiManager::begin()
{
    Serial.println("WiFiManager::begin()");

    WiFi.mode(WIFI_STA);

    Serial.println("WiFi mode configured");

    connect();

    Serial.println("Returned from connect()");
}
// void WiFiManager::begin()
// {
//     WiFi.mode(WIFI_STA);
//     connect();
// }

bool WiFiManager::connect()
{
    Serial.println("Inside connect()");

    Serial.println("Connecting to WiFi...");

    Serial.println();
    Serial.println("Connecting to WiFi...");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    unsigned long start = millis();

    while (!isConnected())
    {
        Serial.print(".");

        delay(500);

        if (millis() - start > WIFI_CONNECT_TIMEOUT_MS)
        {
            Serial.println();
            Serial.println("WiFi connection timeout.");

            return false;
        }
    }

    Serial.println();
    Serial.println("WiFi Connected!");
    Serial.print("IP Address : ");
    Serial.println(WiFi.localIP());

    return true;
}



bool WiFiManager::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

void WiFiManager::ensureConnected()
{
    if (!isConnected())
    {
        Serial.println("WiFi disconnected. Reconnecting...");
        connect();
    }
}