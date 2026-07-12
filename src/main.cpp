#include <Arduino.h>
#include "sensor.h"

// Update these if your wiring is different
#define TRIG_PIN 9
#define ECHO_PIN 10

Sensor sensor(TRIG_PIN, ECHO_PIN);

void setup()
{
    Serial.begin(115200);

    delay(2000);

    Serial.println();
    Serial.println("================================");
    Serial.println("TankSense - Sensor Module");
    Serial.println("================================");

    sensor.begin();
}

void loop()
{
    float distance = sensor.getDistanceCM();

    if (distance < 0)
    {
        Serial.println("No Echo");
    }
    else
    {
        Serial.print("Distance : ");
        Serial.print(distance);
        Serial.println(" cm");
    }

    delay(1000);
}