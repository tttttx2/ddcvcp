#include "DDCVCP.h"
#include <ESP32Lib.h> // Depends on https://github.com/bitluni/ESP32Lib for signal generation for now.

//pin configuration
const int redPin = 14;
const int greenPin = 19;
const int bluePin = 27;
const int hsyncPin = 32;
const int vsyncPin = 33;


DDCVCP ddc;
VGA3Bit vga;


void setup() {
  Serial.begin(9600);
  while (!ddc.begin()) {
    Serial.print(F("-  Unable to find DDC/CI. Trying again in 5 seconds.\n"));
    delay(5000);
  }
  Serial.print(F("-  Found DDC/CI successfully.\n"));
  vga.init(vga.MODE320x240, redPin, greenPin, bluePin, hsyncPin, vsyncPin);
}

void loop() {
    ddc.setBrightness(10);
    delay(3000);
    ddc.setBrightness(50);
    delay(3000);
    ddc.setBrightness(100);
    delay(3000);
}
