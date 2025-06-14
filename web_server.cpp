#include <WebServer.h>
#include <LittleFS.h>
#include "config.h"
#include "net_config.h"

WebServer server(80);

void handleRoot() {
  File file = LittleFS.open("/index.html", "r");
  server.streamFile(file, "text/html");
  file.close();
}

void handleSave() {
  if (server.hasArg("ip")) {
    IPAddress newIP;
    sscanf(server.arg("ip").c_str(), "%hhu.%hhu.%hhu.%hhu", &newIP[0], &newIP[1], &newIP[2], &newIP[3]);
    saveIP(newIP);
    server.send(200, "text/plain", "Saved. Rebooting...");
    delay(500);
    ESP.restart();
  }
}

void startWebServer() {
  LittleFS.begin();
  server.on("/", handleRoot);
  server.on("/save", HTTP_POST, handleSave);
  server.begin();
}