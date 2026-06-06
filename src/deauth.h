#pragma once
#include <Arduino.h>

// Deauth frame structure
typedef struct {
    uint8_t frame_control[2];
    uint8_t duration[2];
    uint8_t station[6];
    uint8_t access_point[6];
    uint8_t sender[6];
    uint8_t sequence_control[2];
    uint16_t reason;
} deauth_frame_t;

// External variables
extern int eliminated_stations;
extern bool attack_active;
extern int deauth_type;
extern deauth_frame_t deauth_frame;

// Functions
void start_deauth(int wifi_number, int attack_type, uint16_t reason);
void start_combined_deauth(uint8_t* bssid, int channel);
void stop_deauth();
void init_deauth();
void set_real_target_info(uint8_t* bssid, int channel);
void send_broadcast_deauth(); 
