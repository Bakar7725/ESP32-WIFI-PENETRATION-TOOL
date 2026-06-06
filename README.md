ESP32 Wi-Fi Penetration Tool - VENOME Cyberpunk Edition

🎯 Overview
VENOME Cyberpunk Edition is a professional-grade Wi-Fi security assessment tool for ESP32, designed for penetration testing and security research. It combines multiple attack vectors with a stunning cyberpunk-themed web interface for comprehensive wireless network auditing.

🔥 Key Features
Feature	Description
Evil Twin Attack	Clone legitimate APs to capture credentials
Devil Twin Attack	Advanced AP cloning with constant-rate deauthentication
4-Way Handshake Capture	Capture and analyze WPA/WPA2 handshakes
PCAP Verifier	Analyze captured handshakes for cracking readiness
Deauthentication Attack	Disconnect clients from target networks
Background Scanning	Automatic channel tracking for roaming APs
Real-time Monitoring	Live dashboard with client tracking
PCAp Export	Hashcat-compatible handshake format

🛠️ Hardware Requirements
Component	Specification
Microcontroller	ESP32 (DOIT DevKit V1 recommended)
Flash Size	4MB minimum (16MB recommended)
USB Cable	Data-capable USB cable
Antenna	Integrated PCB or external (for better range)
Power Source	USB or 5V battery pack
Compatible ESP32 Boards
ESP32 DOIT DevKit V1 ✅

ESP32-WROOM-32 ✅

ESP32-WROVER ✅

NodeMCU-32S ✅

LOLIN32 ✅

percentage




💻 Software Requirements
Development Environment
bash
PlatformIO IDE
  - Version: 6.1.0+
  - Platform: espressif32
  - Framework: Arduino
Dependencies
ini
[env:esp32doit-devkit-v1]
platform = espressif32
board = esp32doit-devkit-v1
framework = arduino
lib_deps =
    ESP32Async/ESPAsyncWebServer
    ESP32Async/AsyncTCP
System Requirements
PlatformIO Core (or VSCode + PlatformIO Extension)

Python 3.7+

Git

USB-to-UART drivers (CP210x, CH340, or FTDI)

📦 Installation
1. Clone the Repository
bash
git clone https://github.com/Bakar7725/ESP32-WIFI-PENETRATION-TOOL.git
cd ESP32-WIFI-PENETRATION-TOOL
2. Build and Upload with PlatformIO
bash
# Build the project
pio run

# Upload to ESP32
pio run --target upload

# Monitor serial output
pio device monitor --baud 115200
🎮 Usage Guide
First Boot
Power on ESP32 - LED indicators will show boot status

Connect to AP - Scan for VENOME v1 (Password: Venome@kali)

Note :
SSID :  VENOME v1 Password : Venome@kali
SSID :  VENOME v2 Password : Venome@kali
SSID :  VENOME v3 Password : Venome@kali

Access Web Interface - Navigate to http://192.168.4.1

Main Dashboard Features
Network Scanning
Click SCAN NETWORKS to discover nearby APs

Networks display:

SSID (name)

Channel

Signal strength (dBm with visual bars)

Security type (OPEN/WPA/WPA2/WPA3)

Approximate range

Target Selection
Click any network row to select target

Selected target shows detailed information

Signal strength displayed with percentage

Available Attacks
Attack	Button	Description
Deauth	⚡ START DEAUTH	Disconnect clients from target AP
Evil Twin	🏠 START EVIL TWIN	Clone AP with credential capture portal
Devil Twin	👿 START DEVIL TWIN	Advanced attack with constant deauth + fake AP
Handshake Capture	🔒 HANDSHAKE CAPTURE	Capture 4-way handshake for cracking
PCAP Verifier	📡 PCAP VERIFIER	Analyze captured handshakes
🎯 Attack Modes
1. Deauthentication Attack
yaml
Type: Denial of Service
Purpose: Disconnect clients from target network
Method: Send forged deauth frames to broadcast address
Rate: 50 packets/second (configurable)
Use Case: Force clients to reconnect (capture handshake)
2. Evil Twin Attack
yaml
Type: Credential Harvesting
Purpose: Clone legitimate AP to capture passwords
Method: 
  - Create identical SSID
  - Host captive portal
  - Forward credentials (optional)
Use Case: Phishing Wi-Fi credentials
3. Devil Twin Attack
yaml
Type: Combined Attack
Purpose: Force reconnection + Credential capture
Method:
  - Clone target AP
  - Send constant deauth packets
  - Background channel scanning
Rate: 50 packets/sec (deauth)
Use Case: Aggressive handshake capture
4. Constant Rate Attack (New)
yaml
Type: High-intensity Deauth
Purpose: Maximum disruption without fake AP
Method:
  - NO fake AP (stealthy)
  - Constant packet rate
  - Background scanning only
Rate: 50 packets/sec CONSTANT
Use Case: Testing without credential capture
🌐 Web Interface
Access Points
Interface	URL	Description
Main Portal	http://192.168.4.1	Evil twin captive portal
Admin Panel	http://192.168.4.1/admin	Attack control dashboard
Monitor	http://192.168.4.1/moniter	Real-time monitoring
Admin Panel Features
Statistics Dashboard
Uptime counter

Free heap memory

Active attack status

Current target info

Control Buttons
Scan Networks

Start/Stop Deauth

Start/Stop Evil Twin

Start/Stop Devil Twin

![Dashboard](./Images/Admin.png)


Evil Twin Portal : 
![Dashboard](./Images/Portal.png)

Evil Twin Client Moniter :
![Dashboard](./Images/Monniter.png)


Handshake Capture :

![Dashboard](./Images/Handshake.png)

PCAP Verifier : 

![Dashboard](./Images/PcapVerify.png)

Network List
Real-time SSID display

Signal strength bars

Security indicators (🔓/🔒)

One-click selection

Monitor Dashboard
text
[ MONITOR DASHBOARD ]
├── Current connected clients
├── Total unique clients
├── Password attempts (real-time)
├── Client history
└── Attack status indicators
📡 API Reference
Web Endpoints (PacketWiFi Mode)
Endpoint	Method	Description
/	GET	Evil twin portal page
/admin	GET	Admin control panel
/moniter	GET	Monitoring dashboard

⚖️ Legal Disclaimer
text
THIS SOFTWARE IS PROVIDED FOR EDUCATIONAL PURPOSES ONLY.

By using this software, you agree that:
1. You will only test networks you own or have written permission to test
2. You understand the laws regarding Wi-Fi security testing in your jurisdiction
3. The author assumes NO liability for misuse or damage
4. Unauthorized access to computer systems is illegal
5. You will use this tool responsibly and ethically

Violation of these terms may result in:
- Civil liability
- Criminal prosecution
- Termination of service agreements
🎨 Credits
Development
Author: Bakar7725

Version: 7.0 Cyberpunk Edition

Libraries
ESPAsyncWebServer - ESP32 Async Web Server

AsyncTCP - Async TCP Library

PlatformIO - Build System

Fonts
Orbitron by The League of Moveable Type (SIL Open Font License)

Inspiration
Cyberpunk 2077 aesthetic




