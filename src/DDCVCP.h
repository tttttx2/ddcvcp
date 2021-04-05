/*
  DDCVCP.h - Library for controlling monitors over DDC/CI.
  Created by Toni Tanner, 2021.
*/

#ifndef DDCVCP_h
#define DDCVCP_h

#include <Wire.h>
#include "Arduino.h"


class DDCVCP
{
  public:
    DDCVCP();
    bool begin();
    void setBrightness(int value);
    uint16_t getBrightness();
    void setVCP(byte op, uint16_t value);
    uint16_t getVCP(byte op);
    void setSource(uint16_t value);
    uint16_t getSource();
    void setPower(bool value);
    bool getPower();
  private:
    uint8_t _I2CAddress = 0x37;
};

#endif

 
