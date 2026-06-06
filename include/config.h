#pragma once

#include <Arduino.h>

// Comment this line to disable debug output
#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINTF(...) Serial.printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(x)
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINTF(...)
#endif

// ==================== DEAUTH CONFIG ====================
#define DEAUTH_TYPE_SINGLE 0
#define DEAUTH_TYPE_BROADCAST 2
#define NUM_FRAMES_PER_DEAUTH 5

// ==================== WIFI CONFIG ====================

#define MAX_NETWORKS 16

// ==================== NETWORK STRUCT ====================
struct _Network {
  String ssid;
  uint8_t bssid[6];
  int ch;
  int rssi; // Add this line
  uint8_t auth_mode; // Add this line for security type
};