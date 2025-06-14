# BAS-ESP32
# BAS-Brick

**BAS-Brick** is a portable, ESP32-based field tool for building automation professionals. Designed around the WT32-ETH01, it supports Ethernet and Wi-Fi scanning of BACnet/IP and Modbus TCP devices, includes RS-485 for MS/TP and RTU protocols, and features a local OLED display plus a web-based configuration portal.

---

## 🚀 Features

- ⚡ **Ethernet and Wi-Fi** support (auto-fallback)
- 🌐 **Web UI** for setting static IP and triggering scans
- 🧾 **BACnet/IP and Modbus TCP discovery** (coming soon)
- 🔌 **RS-485 port** for BACnet MS/TP or Modbus RTU
- 📺 **OLED display** shows IP address, scan status, and summary
- 🧠 **Preferences storage** using non-volatile flash
- 🔁 **Factory reset** via GPIO button
- 🔐 Designed for **field use** — compact and rugged

---

## 🔧 Hardware Requirements

| Component | Description |
|----------|-------------|
| [WT32-ETH01](https://www.wireless-tag.com/wt32-eth01/) | ESP32-based controller with Ethernet |
| MAX485 RS-485 Module | For MS/TP or Modbus RTU |
| 2.42" OLED SSD1309 (SPI) | IP display and status UI |
| USB-to-Serial Adapter (3.3V logic) | For flashing firmware |
| Pushbutton | For factory reset |
| Power Supply (5V) | USB or regulated external power |

---

## 🔌 Wiring Summary

### OLED (SSD1309 SPI)
| Pin | WT32-ETH01 GPIO |
|-----|-----------------|
| CLK (SCK) | 18 |
| MOSI (SDA) | 23 |
| CS | 5 |
| DC | 16 |
| RES | 17 |
| GND | GND |
| VCC | 5V or 3.3V (check module) |

### RS-485 (MAX485)
| Pin | WT32-ETH01 GPIO |
|-----|-----------------|
| RO | 4 (RX) |
| DI | 2 (TX) |
| DE & RE (tied) | 15 |
| GND | GND |
| VCC | 5V |

### Reset Button
| Pin | WT32-ETH01 GPIO |
|-----|-----------------|
| One side | 13 |
| Other side | GND |

---

## 📦 Repository Structure

---

## 🧑‍💻 Getting Started

1. **Install Board Support**
   - Arduino ESP32 URL:  
     `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`

2. **Flash the WT32-ETH01**
   - Use Arduino IDE or PlatformIO
   - Upload LittleFS files via plugin or CLI (`pio run -t uploadfs`)

3. **Connect Ethernet**
   - Device boots with saved or default static IP (shown on OLED)
   - If Ethernet unavailable, boots Wi-Fi AP: `BAS-Brick` (password: `brick123`)
   - Open browser to `192.168.4.1` to set static IP

4. **Optional: Hold GPIO13 LOW on boot** to reset to factory defaults.

---

## 🔜 Roadmap

- ✅ Static IP config (Web UI)
- ✅ Preferences flash storage
- ✅ OLED UI
- 🔄 BACnet/IP device discovery
- 🔄 Modbus TCP scanner
- 🔄 RS-485 protocol support (BACnet MS/TP & Modbus RTU)
- 🔄 CSV log output to USB or SD
- 🔒 Enclosure & DIN mount support

---

## 📄 License

MIT License — use freely, contribute generously!

---

## 🙏 Credits

- Based on ESP32 + Ethernet (WT32-ETH01)
- SSD1309 OLED via U8g2lib
- Web UI served via ESP32 LittleFS

BAS-ESP32
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
