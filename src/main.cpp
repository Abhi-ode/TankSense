#include <Arduino.h>

void setup()
{
    Serial.begin(115200);

    delay(2000);

    Serial.println();
    Serial.println("===============================");
    Serial.println("TankSense PlatformIO Test");
    Serial.println("===============================");
}

void loop()
{
    Serial.println("ESP32-C3 Running...");
    delay(1000);
}