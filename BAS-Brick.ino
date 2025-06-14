#include "config.h"
#include "net_config.h"
#include "oled_display.h"
#include "web_server.h"
#include "update_ota.h"
#include "scan_simulator.h"

void setup() {
  Serial.begin(115200);
  initOLED();
  initNetwork();
  showIP(getCurrentIP(), isUsingWiFi());
  startWebServer();
  handleOTA();
}

void loop() {
  runScanSimulator();  // Replace with scanModbus() or scanBACnet() later
  delay(10000);
}