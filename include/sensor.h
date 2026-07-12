#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor
{
public:
    Sensor(uint8_t trigPin, uint8_t echoPin);

    void begin();

    // Returns filtered distance
    float getDistanceCM();

private:
    // Takes one raw measurement
    float getRawDistanceCM();

    uint8_t _trigPin;
    uint8_t _echoPin;
};

#endif