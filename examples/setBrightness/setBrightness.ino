#include "DDCVCP.h" 

DDCVCP ddc;

void setup() {
  Serial.begin(9600);
  while (!ddc.begin()) {
    Serial.print(F("-  Unable to find DDC/CI. Trying again in 5 seconds.\n"));
    delay(5000);
  }
  Serial.print(F("-  Found DDC/CI successfully.\n"));
}

void loop() {
    ddc.setBrightness(10);
    delay(3000);
    ddc.setBrightness(50);
    delay(3000);
    ddc.setBrightness(100);
    delay(3000);
}
