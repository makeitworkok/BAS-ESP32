#include "modbus_scan.h"
#include "modbus_rtu.h"
#include <Arduino.h>

void scanModbusRTUDevices() {
  Serial.println("Scanning Modbus RTU bus...");
  for (uint8_t id = 1; id <= 247; id++) {
    if (pingModbusDevice(id)) {
      Serial.print("Found device at ID: ");
      Serial.println(id);
    }
    delay(50);
  }
}