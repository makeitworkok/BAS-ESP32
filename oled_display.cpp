#include <U8g2lib.h>
#include "oled_display.h"
#include "config.h"

U8G2_SSD1309_128X64_NONAME2_F_SW_I2C display(U8G2_R0, OLED_CLK, OLED_MOSI, OLED_CS, OLED_DC, OLED_RST);

void initOLED() {
  display.begin();
  display.clearBuffer();
  display.setFont(u8g2_font_ncenB08_tr);
}

void showIP(IPAddress ip, bool wifi) {
  display.clearBuffer();
  display.setCursor(0, 16);
  display.print(wifi ? "Wi-Fi: " : "ETH: ");
  display.print(ip);
  display.sendBuffer();
}

void showScanStatus(const char* msg) {
  display.setCursor(0, 32);
  display.print(msg);
  display.sendBuffer();
}