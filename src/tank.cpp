#include "tank.h"
#include "config.h"

Tank::Tank(Sensor &sensor)
    : _sensor(sensor)
{
}

TankReading Tank::read()
{
    TankReading reading;

    reading.distanceCM = _sensor.getDistanceCM();

    if (reading.distanceCM < 0)
    {
        reading.waterHeightCM = -1;
        reading.percentage = -1;
        reading.status = TankStatus::Empty;

        return reading;
    }

    reading.waterHeightCM =
        TANK_HEIGHT_CM -
        (reading.distanceCM - SENSOR_OFFSET_CM);

    if (reading.waterHeightCM < 0)
        reading.waterHeightCM = 0;

    if (reading.waterHeightCM > TANK_HEIGHT_CM)
        reading.waterHeightCM = TANK_HEIGHT_CM;

    reading.percentage =
        (reading.waterHeightCM / TANK_HEIGHT_CM) * 100.0f;

    reading.status = getStatus(reading.percentage);

    return reading;
}

TankStatus Tank::getStatus(float percentage)
{
    if (percentage < 10)
        return TankStatus::Empty;

    if (percentage < 30)
        return TankStatus::LowLevel;

    if (percentage < 60)
        return TankStatus::MediumLevel;

    if (percentage < 90)
        return TankStatus::HighLevel;

    return TankStatus::Full;
}