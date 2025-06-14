BAS-ESP32

BAS-ESP32 is a portable, ESP32-based field tool for building automation professionals. Designed around the WT32-ETH01, it supports Ethernet and Wi-Fi scanning of BACnet/IP and Modbus TCP devices, includes RS-485 for MS/TP and RTU protocols, and features a local OLED display plus a web-based configuration portal.

⸻

🚀 Features
	•	⚡ Ethernet and Wi-Fi support (auto-fallback)
	•	🌐 Web UI for setting static IP and triggering scans
	•	🧾 BACnet/IP and Modbus TCP discovery
	•	🔌 RS-485 port for BACnet MS/TP or Modbus RTU
	•	📺 OLED display shows IP address, scan status, and summary
	•	🧠 Preferences storage using non-volatile flash
	•	🔁 Factory reset via GPIO button
	•	🔐 Designed for field use — compact and rugged
	•	📃 CSV log output for scan results
	•	⬆️ OTA updates via web interface
	•	✨ Scan simulation mode for development/testing

⸻

🔧 Hardware Requirements

Component	Description
WT32-ETH01	ESP32-based controller with Ethernet
MAX485 RS-485 Module	For MS/TP or Modbus RTU
2.42” OLED SSD1309 (SPI)	IP display and status UI
USB-to-Serial Adapter (3.3V logic)	For flashing firmware
Pushbutton	For factory reset
Power Supply (5V)	USB or regulated external power


⸻

🔌 Wiring Summary

OLED (SSD1309 SPI)

Pin	WT32-ETH01 GPIO
CLK (SCK)	18
MOSI (SDA)	23
CS	5
DC	16
RES	17
GND	GND
VCC	5V or 3.3V (check module)

RS-485 (MAX485)

Pin	WT32-ETH01 GPIO
RO	4 (RX)
DI	2 (TX)
DE & RE (tied)	15
GND	GND
VCC	5V

Reset Button

Pin	WT32-ETH01 GPIO
One side	13
Other side	GND


⸻

🖧 Wiring Diagram

                          +-----------------------------+
                          |         WT32-ETH01          |
                          |     (ESP32 + Ethernet)      |
                          |                             |
                          |                             |
         GND o------------+-----------------------------+
         5V  o----+                                        
                  |                                        
                  |                  +-----------------+      
                  +----------------->| VCC             |        
                                     |                 |
OLED Display (SSD1309)               | OLED Display    |
--------------------------------     | (SPI, 2.42")    |
  CLK (SCK)   -> GPIO18 -------------| D0 (SCK)        |
  MOSI (SDA)  -> GPIO23 -------------| D1 (MOSI)       |
  CS          -> GPIO5  -------------| CS              |
  DC          -> GPIO16 -------------| DC              |
  RST         -> GPIO17 -------------| RST             |
  GND         -> GND  ---------------| GND             |
                                     +-----------------+

MAX485 RS-485 Module
----------------------
  RO  -> GPIO4   (UART RX)
  DI  -> GPIO2   (UART TX)
  DE+RE (tied) -> GPIO15 (Direction control)
  VCC -> 5V
  GND -> GND
  A/B -> RS-485 network

Factory Reset Button
----------------------
  One side -> GPIO13
  Other side -> GND
  (Use INPUT_PULLUP in code)


⸻

📦 Repository Structure

BAS-ESP32/
├── BAS-ESP32.ino             # Main app entry
├── config.h                  # GPIO definitions and constants
├── net_config.*              # Network + preferences
├── oled_display.*            # OLED setup and display
├── web_server.*              # Web UI endpoint logic
├── update_ota.*              # OTA update support
├── scan_simulator.*          # Optional simulation mode
├── modbus_scan.*             # Modbus TCP scan logic
├── bacnet_scan.*             # BACnet/IP scan logic
└── data/
    └── index.html           # Web interface (LittleFS)


⸻

👩‍💻 Getting Started

Arduino IDE Setup
	1.	Install ESP32 Board Support
	•	Add URL to Preferences:

https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json


	•	Board: ESP32 Dev Module
	•	Partition Scheme: Default (4MB with spiffs)
	•	Upload Speed: 921600
	•	Core Debug Level: None

	2.	Install Required Libraries
	•	U8g2
	•	ESPAsyncWebServer (from GitHub)
	•	LittleFS_esp32
	3.	Upload Web Files
	•	Install ESP32FS plugin
	•	Place index.html inside data/
	•	Use Tools → ESP32 Sketch Data Upload
	4.	Connect Ethernet
	•	Device boots with saved or default IP (shown on OLED)
	•	If Ethernet unavailable, starts AP BAS-ESP32 (password: esp32brick)
	•	Open browser to 192.168.4.1 to set static IP
	5.	Optional: Hold GPIO13 LOW on boot to reset preferences.
	6.	Download ZIP
	•	Click here to download the latest ZIP (github.com/makeitwork/BAS-ESP32)

PlatformIO Setup

[env:wt32-eth01]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
upload_speed = 921600

lib_deps =
  bodmer/U8g2@^2.34.22
  ESP Async WebServer
  ESPAsyncTCP
  LittleFS_esp32
  espressif/arduino-esp32@^2.0.14

build_flags =
  -DARDUINO_RUNNING_CORE=1
  -DARDUINO_EVENT_RUNNING_CORE=0
  -DESP32_DEV
  -DLED_BUILTIN=2

monitor_filters = colorize

Upload web files: pio run -t uploadfs

⸻

📊 Roadmap
	•	Static IP config (Web UI)
	•	Preferences flash storage
	•	OLED UI
	•	Factory reset via button
	•	OTA updates from Web UI
	•	CSV export of scan results
	•	Scan simulation mode
	•	BACnet/IP discovery tool
	•	Modbus TCP scanner
	•	RS-485 BACnet MS/TP integration
	•	USB logging or SD card output

⸻

📄 License

MIT License — use freely, contribute generously!

⸻

🙏 Credits
	•	ESP32 Ethernet via WT32-ETH01 by Wireless-Tag
	•	SSD1309 OLED driven via U8g2lib
	•	Async Web Server by me-no-dev
	•	Designed by building automation pros, for pros
