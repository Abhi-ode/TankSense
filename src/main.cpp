#include <Arduino.h>

#include "config.h"
#include "sensor.h"
#include "tank.h"

Sensor sensor(TRIG_PIN, ECHO_PIN);
Tank tank(sensor);

String statusToString(TankStatus status)
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

void setup()
{
    Serial.begin(SERIAL_BAUDRATE);

    delay(2000);

    Serial.println();
    Serial.println("=================================");
    Serial.println("TankSense");
    Serial.println("=================================");

    sensor.begin();
}

void loop()
{
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