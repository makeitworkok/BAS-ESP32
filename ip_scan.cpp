#include <WiFi.h>
#include "ip_scan.h"
#include <ESPmDNS.h>

void scanIPNetwork() {
  IPAddress localIP = WiFi.localIP();
  IPAddress subnet = WiFi.subnetMask();
  Serial.printf("Starting IP scan on network: %s/%s\n", localIP.toString().c_str(), subnet.toString().c_str());

  // Only support /24 for now
  IPAddress base = localIP;
  base[3] = 1;

  for (int i = 1; i < 255; i++) {
    IPAddress target = base;
    target[3] = i;
    if (target == localIP) continue;

    WiFiClient client;

    Serial.printf("Probing %s... ", target.toString().c_str());
    if (client.connect(target, 80)) {
      Serial.print("[HTTP] ");
      client.stop();
    }
    if (client.connect(target, 443)) {
      Serial.print("[HTTPS] ");
      client.stop();
    }
    if (client.connect(target, 22)) {
      Serial.print("[SSH] ");
      client.stop();
    }

    // Get MAC using ESP32 ARP table
    wifi_sta_list_t stationList;
    tcpip_adapter_sta_list_t adapterList;
    esp_wifi_ap_get_sta_list(&stationList);
    tcpip_adapter_get_sta_list(&stationList, &adapterList);
    for (int j = 0; j < adapterList.num; j++) {
      if (adapterList.sta[j].ip.addr == target) {
        const uint8_t* mac = adapterList.sta[j].mac;
        Serial.printf("[MAC %02X:%02X:%02X:%02X:%02X:%02X] ",
          mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        break;
      }
    }

    Serial.println();
    delay(10);
  }

  Serial.println("IP scan complete.");
}