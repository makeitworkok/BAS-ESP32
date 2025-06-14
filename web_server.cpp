#include <Arduino.h>
#include <WebServer.h>
#include <Preferences.h>
#include "modbus_rtu.h"
#include "modbus_scan.h"
#include "mstp_scan/mstp_scan.h"

WebServer server(80);

void handleModbusConfig() {
  if (server.hasArg("baud")) {
    int baud = server.arg("baud").toInt();
    if (baud >= 1200 && baud <= 115200) {
      Preferences prefs;
      prefs.begin("modbus", false);
      prefs.putInt("baud", baud);
      prefs.end();
      server.send(200, "text/plain", "Baud rate set. Rebooting...");
      delay(500);
      ESP.restart();
    } else {
      server.send(400, "text/plain", "Invalid baud rate");
    }
  }
}

void handleRS485Protocol() {
  if (server.hasArg("protocol")) {
    String proto = server.arg("protocol");
    if (proto == "modbus" || proto == "bacnet") {
      Preferences prefs;
      prefs.begin("rs485", false);
      prefs.putString("protocol", proto);
      prefs.end();
      server.send(200, "text/plain", "Protocol set. Rebooting...");
      delay(500);
      ESP.restart();
    } else {
      server.send(400, "text/plain", "Invalid protocol selection");
    }
  }
}

void handleModbusScan() {
  server.send(200, "text/plain", "Modbus scan started. Check serial log.");
  scanModbusRTUDevices();
}

void handleMSTPScan() {
  server.send(200, "text/plain", "BACnet MS/TP scan started. Check serial log.");
  startMSTPScan();
}

void handleRoot() {
  server.send(200, "text/html", "<html><body><h1>BAS-ESP32 Web Server</h1></body></html>");
}

void startWebServer() {
  server.on("/", handleRoot);
  server.on("/modbus-config", HTTP_POST, handleModbusConfig);
  server.on("/rs485-protocol", HTTP_POST, handleRS485Protocol);
  server.on("/start-modbus-scan", HTTP_POST, handleModbusScan);
  server.on("/start-mstp-scan", HTTP_POST, handleMSTPScan);

  
  server.on("/start-ip-scan", HTTP_POST, []() {
    server.send(200, "text/plain", "IP scan started. Check serial log.");
    scanIPNetwork();
  });
  server.begin();
  Serial.println("Web server started.");
}