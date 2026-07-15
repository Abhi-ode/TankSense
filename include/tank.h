#ifndef TANK_H
#define TANK_H

#include <Arduino.h>
#include "sensor.h"

enum class TankStatus
{
    Empty,
    LowLevel,
    MediumLevel,
    HighLevel,
    Full
};

struct TankReading
{
    float distanceCM;
    float waterHeightCM;
    float percentage;
    TankStatus status;
};

class Tank
{
public:
    Tank(Sensor &sensor);

    TankReading read();

private:
    Sensor &_sensor;

    TankStatus getStatus(float percentage);
};

#endif