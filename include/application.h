#ifndef APPLICATION_H
#define APPLICATION_H

#include <Arduino.h>

#include "sensor.h"
#include "tank.h"
#include "wifi_manager.h"

class Application
{
public:
    Application();

    void begin();

    void run();

private:
    Sensor sensor;
    Tank tank;
    WiFiManager wifiManager;

    String statusToString(TankStatus status);
};

#endif