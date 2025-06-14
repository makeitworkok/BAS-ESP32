#include "scan_simulator.h"
#include "oled_display.h"

void runScanSimulator() {
  showScanStatus("Sim scan...");
  delay(2000);
  showScanStatus("Found 3 devices");
}