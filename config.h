#pragma once

// RS-485
#define RS485_RX   4
#define RS485_TX   2
#define RS485_DIR  15

// OLED Display (SPI)
#define OLED_CLK   18
#define OLED_MOSI  23
#define OLED_CS    5
#define OLED_DC    16
#define OLED_RST   17

// Factory Reset Button
#define RESET_PIN  13

// Ethernet IP Defaults
#define DEFAULT_IP      IPAddress(10,46,12,2)
#define DEFAULT_GATEWAY IPAddress(10,46,12,1)
#define DEFAULT_SUBNET  IPAddress(255,255,255,0)