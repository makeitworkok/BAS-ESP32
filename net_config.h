#pragma once
#include <IPAddress.h>

void initNetwork();
IPAddress getCurrentIP();
bool isUsingWiFi();
void resetPreferences();