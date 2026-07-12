#include "sensor.h"

Sensor::Sensor(uint8_t trigPin, uint8_t echoPin)
{
    _trigPin = trigPin;
    _echoPin = echoPin;
}

void Sensor::begin()
{
    pinMode(_trigPin, OUTPUT);
    pinMode(_echoPin, INPUT);

    digitalWrite(_trigPin, LOW);
}

//----------------------------------------------------
// Takes ONE measurement only (No filtering)
//----------------------------------------------------
float Sensor::getRawDistanceCM()
{
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);

    long duration = pulseIn(_echoPin, HIGH, 30000);

    if (duration == 0)
    {
        return -1;
    }

    return duration * 0.0343f / 2.0f;
}

//----------------------------------------------------
// Public function (currently just returns raw value)
// We'll add filtering in the next commit.
//----------------------------------------------------
float Sensor::getDistanceCM()
{
    return getRawDistanceCM();
}