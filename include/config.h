#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include "secrets.h"

/*==================================================
  Firmware
==================================================*/
constexpr char FIRMWARE_VERSION[] = "0.1.0";

/*==================================================
  Debug
==================================================*/
constexpr bool DEBUG_SENSOR = false;
constexpr bool DEBUG_WIFI = false;
constexpr bool DEBUG_TELEGRAM = false;

/*==================================================
  Serial
==================================================*/
constexpr uint32_t SERIAL_BAUDRATE = 115200;

/*==================================================
  HC-SR04
==================================================*/
constexpr uint8_t TRIG_PIN = 3;
constexpr uint8_t ECHO_PIN = 2;

constexpr uint8_t SENSOR_SAMPLE_COUNT = 7;
constexpr uint32_t SENSOR_DELAY_MS = 30;
constexpr uint32_t SENSOR_TIMEOUT_US = 30000;

/*==================================================
  Tank
==================================================*/
constexpr float TANK_HEIGHT_CM = 150.0f;

/*==================================================
  WiFi
==================================================*/

constexpr uint32_t WIFI_CONNECT_TIMEOUT_MS = 15000;
constexpr uint32_t WIFI_RETRY_INTERVAL_MS = 5000;

// Distance between sensor and water when tank is full
constexpr float SENSOR_OFFSET_CM = 0.0f;

/*==================================================
  Timing
==================================================*/
constexpr uint32_t SENSOR_UPDATE_INTERVAL_MS = 1000;

#endif