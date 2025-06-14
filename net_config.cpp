#include "config.h"
#include <ETH.h>
#include <WiFi.h>
#include <Preferences.h>

Preferences prefs;
bool wifiFallback = false;
IPAddress currentIP;

void resetPreferences() {
  prefs.begin("netcfg", false);
  prefs.clear();
  prefs.end();
}

IPAddress getSavedIP() {
  prefs.begin("netcfg", true);
  uint8_t ip[4];
  if (prefs.getBytes("ip", ip, 4) == 4) {
    prefs.end();
    return IPAddress(ip[0], ip[1], ip[2], ip[3]);
  }
  prefs.end();
  return DEFAULT_IP;
}

void saveIP(IPAddress ip) {
  prefs.begin("netcfg", false);
  uint8_t ipBytes[4] = {ip[0], ip[1], ip[2], ip[3]};
  prefs.putBytes("ip", ipBytes, 4);
  prefs.end();
}

void initNetwork() {
  pinMode(RESET_PIN, INPUT_PULLUP);
  if (digitalRead(RESET_PIN) == LOW) {
    resetPreferences();
    delay(1000);
    ESP.restart();
  }

  IPAddress ip = getSavedIP();
  currentIP = ip;
  if (!ETH.config(ip, DEFAULT_GATEWAY, DEFAULT_SUBNET)) {
    wifiFallback = true;
    WiFi.softAP("BAS-Brick", "brick123");
    currentIP = WiFi.softAPIP();
  }

  ETH.begin();
}

IPAddress getCurrentIP() {
  return currentIP;
}

bool isUsingWiFi() {
  return wifiFallback;
}