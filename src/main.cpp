#include <Arduino.h>
#include "application.h"

Application app;

void setup()
{
    app.begin();
}

void loop()
{
    app.run();
}