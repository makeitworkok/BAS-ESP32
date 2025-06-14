#include "mstp_scan.h"
#include "../bacnet_mstp/bacnet_mstp.h"
#include <Arduino.h>

void startMSTPScan() {
  Serial.println("Starting BACnet MS/TP scan...");
  sendWhoIs();

  unsigned long timeout = millis() + 3000;
  while (millis() < timeout) {
    if (MSTP.available()) {
      Serial.print("Response: ");
      while (MSTP.available()) {
        uint8_t b = MSTP.read();
        Serial.printf("%02X ", b);
      }
      Serial.println();
    }
    delay(10);
  }

  Serial.println("MS/TP scan complete.");
}