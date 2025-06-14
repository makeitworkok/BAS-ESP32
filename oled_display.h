#pragma once
#include <IPAddress.h>

void initOLED();
void showIP(IPAddress ip, bool wifi);
void showScanStatus(const char* msg);