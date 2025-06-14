#include "bacnet_mstp.h"
#include <HardwareSerial.h>
#include "config.h"

HardwareSerial MSTP(1);  // UART1

void beginBACnetMSTP() {
  pinMode(RS485_DIR, OUTPUT);
  digitalWrite(RS485_DIR, LOW); // Listen mode
  MSTP.begin(38400, SERIAL_8N1, RS485_RX, RS485_TX);
  Serial.println("BACnet MS/TP initialized at 38400 baud");
}

void sendWhoIs() {
  uint8_t whoIs[] = {
    0x55, 0xFF, 0x10, // Preamble
    0x0A,             // Frame type: BACnet DataExpectingReply
    0xFF,             // Dest MAC
    0x00,             // Src MAC
    0x00,             // Length MSB
    0x0C,             // Length LSB
    0x01,             // BACnet type
    0x20,             // Network message type: Who-Is
    0xFF, 0xFF, 0xFF, 0xFF // Optional limits (not used here)
  };

  digitalWrite(RS485_DIR, HIGH);
  delayMicroseconds(20);
  MSTP.write(whoIs, sizeof(whoIs));
  MSTP.flush();
  delayMicroseconds(20);
  digitalWrite(RS485_DIR, LOW);

  Serial.println("Who-Is sent on MS/TP");
}