#include "modbus_rtu.h"
#include <HardwareSerial.h>
#include <Preferences.h>
#include "config.h"

HardwareSerial RS485(1);

void setTransmit(bool tx) {
  digitalWrite(RS485_DIR, tx ? HIGH : LOW);
  delayMicroseconds(10);
}

int getModbusBaudRate() {
  Preferences prefs;
  prefs.begin("modbus", true);
  int baud = prefs.getInt("baud", 9600);
  prefs.end();
  return baud;
}

void beginModbusRTU() {
  pinMode(RS485_DIR, OUTPUT);
  setTransmit(false);
  int baud = getModbusBaudRate();
  RS485.begin(baud, SERIAL_8N1, RS485_RX, RS485_TX);
}

bool pingModbusDevice(uint8_t slaveId) {
  uint8_t frame[8] = { slaveId, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00 };

  uint16_t crc = 0xFFFF;
  for (int i = 0; i < 6; i++) {
    crc ^= frame[i];
    for (int j = 0; j < 8; j++) {
      if (crc & 1) crc = (crc >> 1) ^ 0xA001;
      else crc >>= 1;
    }
  }
  frame[6] = crc & 0xFF;
  frame[7] = crc >> 8;

  setTransmit(true);
  RS485.write(frame, 8);
  RS485.flush();
  setTransmit(false);

  uint32_t timeout = millis() + 300;
  while (RS485.available() < 5 && millis() < timeout) {
    delay(1);
  }

  return RS485.available() >= 5;
}