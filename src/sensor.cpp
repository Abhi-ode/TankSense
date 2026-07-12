#include "sensor.h"
#include "config.h"

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
    const int MAX_SAMPLES = 7;

    float values[MAX_SAMPLES];
    int count = 0;

    // Collect valid readings
    for (int i = 0; i < MAX_SAMPLES; i++)
    {
        float d = getRawDistanceCM();

        if (d >= 2.0f && d <= 400.0f)
        {
            values[count++] = d;
        }

        delay(SENSOR_DELAY_MS); // HC-SR04 datasheet recommendation
    }

    // temp code
    if (DEBUG_SENSOR)
    {
        Serial.println("\n------------------------");
        Serial.println("Raw Valid Samples:");

        for (int i = 0; i < count; i++)
        {
            Serial.print(values[i]);
            Serial.print(" ");
        }
    }

    Serial.println();

    if (count == 0)
    {
        return -1;
    }

    // Bubble sort
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (values[i] > values[j])
            {
                float temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }

    // Temp code
    if (DEBUG_SENSOR)
    {
        Serial.println("Sorted Samples:");

        for (int i = 0; i < count; i++)
        {
            Serial.print(values[i]);
            Serial.print(" ");
        }

        Serial.println();
    }

    // Median index
    int mid = count / 2;

    // Temp code
    if (DEBUG_SENSOR)
    {
        Serial.print("Median Value: ");
        Serial.println(values[mid]);
    }

    // Average median and neighbors
    float sum = 0;
    int samples = 0;

    for (int i = mid - 1; i <= mid + 1; i++)
    {
        if (i >= 0 && i < count)
        {
            sum += values[i];
            samples++;
        }
    }

    // Temp code
    if (DEBUG_SENSOR)
    {
        Serial.print("Final Filtered Value: ");
        Serial.println(sum / samples);
    }

    Serial.println("------------------------");
    return sum / samples;
}