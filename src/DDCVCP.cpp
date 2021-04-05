/*
  DDCVCP.cpp - Library for controlling monitors over DDC/CI.
  Created by Toni Tanner, 2021.
*/

#include "Arduino.h"
#include "DDCVCP.h"

DDCVCP::DDCVCP()
{

}

bool DDCVCP::begin() {
  Wire.begin();
  Wire.beginTransmission(_I2CAddress);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}

// op: VCP opcode. Can be found with ddc capabilities
// value: 16bit value
void DDCVCP::setVCP(byte op, uint16_t value) {
  Wire.beginTransmission(_I2CAddress);
  Wire.write(0x51);
  Wire.write(0x84);
  Wire.write(0x03);
  Wire.write(op);
  Wire.write(byte(value >> 8));
  Wire.write(byte(value));
  Wire.write((_I2CAddress << 1) ^ 0x51 ^ 0x84 ^ 0x03 ^ op ^ byte(value >> 8)^byte(value)); //XOR checksum. Include all bytes sent, including slave address!
  Wire.endTransmission();
}

uint16_t DDCVCP::getVCP(byte op) {
  Wire.beginTransmission(_I2CAddress);
  Wire.write(0x51);
  Wire.write(0x82);
  Wire.write(0x01);
  Wire.write(op);
  Wire.write((_I2CAddress << 1) ^ 0x51 ^ 0x82 ^ 0x01 ^ op); //XOR checksum. Include all bytes sent, including slave address!
  Wire.endTransmission();
  delay(40);
  Wire.requestFrom(_I2CAddress, 12);
  byte response[12];
  int i = 0;
  while (Wire.available())   // slave may send less than requested
  {
    byte c = Wire.read();    // receive a byte as character
    response[i] = c;
    i++;
    //Serial.printf("%x ",c);         // print the character
  }
  return (response[8] << 8) + response[9];
}

void DDCVCP::setBrightness(int value)
{
  if (value > 100) {
    value = 100;
  }
  setVCP(0x10, value); 
}

uint16_t DDCVCP::getBrightness()
{
  return getVCP(0x10);
} 

// 0x01:VGA, 0x03:DVI, 0x0f:DP
void DDCVCP::setSource(uint16_t value) {
  setVCP(0x60, value);
}

uint16_t DDCVCP::getSource() {
  return getVCP(0x60);
}


// true:on, false:suspend
void DDCVCP::setPower(bool value) {
  if (value) {
    setVCP(0xD6, 0x01);
  }
  else {
    setVCP(0xD6, 0x03);
  }
}

bool DDCVCP::getPower(){
  byte power = getVCP(0xD6);
  if (power==0x01){
    return true;
  }
  return false;
}
