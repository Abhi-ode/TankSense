#include "application.h"
#include "config.h"

Application::Application()
    : sensor(TRIG_PIN, ECHO_PIN),
      tank(sensor)
{
}

void Application::begin()
{
    Serial.begin(SERIAL_BAUDRATE);

    delay(1000);

    Serial.println();
    Serial.println("=================================");
    Serial.println("TankSense");
    Serial.print("Firmware : ");
    Serial.println(FIRMWARE_VERSION);
    Serial.println("=================================");

    sensor.begin();

    wifiManager.begin();
}

String Application::statusToString(TankStatus status)
{
    switch (status)
    {
    case TankStatus::Empty:
        return "EMPTY";

    case TankStatus::LowLevel:
        return "LOW";

    case TankStatus::MediumLevel:
        return "MEDIUM";

    case TankStatus::HighLevel:
        return "HIGH";

    case TankStatus::Full:
        return "FULL";

    default:
        return "UNKNOWN";
    }
}


void Application::run()
{
    Serial.println("=================================");
    Serial.print("WiFi Connected : ");
    Serial.println(wifiManager.isConnected() ? "YES" : "NO");

    Serial.print("IP Address : ");
    Serial.println(WiFi.localIP());

    delay(5000);


    // Ensure WiFi is connected
    wifiManager.ensureConnected();

    // Read tank information
    TankReading reading = tank.read();

    if (reading.distanceCM < 0)
    {
        Serial.println("Sensor Error");
    }
    else
    {
        Serial.println("--------------------------------");

        Serial.print("Distance      : ");
        Serial.print(reading.distanceCM);
        Serial.println(" cm");

        Serial.print("Water Height  : ");
        Serial.print(reading.waterHeightCM);
        Serial.println(" cm");

        Serial.print("Fill          : ");
        Serial.print(reading.percentage);
        Serial.println(" %");

        Serial.print("Status        : ");
        Serial.println(statusToString(reading.status));

        Serial.println("--------------------------------");
    }

    delay(SENSOR_UPDATE_INTERVAL_MS);
}