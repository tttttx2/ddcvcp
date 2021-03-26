#include <Wire.h>
void setup() {

  Wire.begin();                // join i2c bus (address optional for master)

  Serial.begin(9600);          // start serial communication at 9600bps
  delay(2000);
}

byte i2c_port = 0x37; //0x6E>>1


// op: VPC opcode. Can be found with ddc capabilities
// value: 16bit value
void setVPC(byte op, uint16_t value) { 
  Wire.beginTransmission(i2c_port);
  Wire.write(0x51);
  Wire.write(0x84);
  Wire.write(0x03);
  Wire.write(op);
  Wire.write(byte(value>>8));
  Wire.write(byte(value));
  Wire.write((i2c_port<<1)^0x51^0x84^0x03^op^byte(value>>8)^byte(value)); //XOR checksum. Include all bytes sent, including slave address!
  Wire.endTransmission();
  
}

// 0-100
void setBrightness(uint16_t value){
  if (value > 100){
    value=100;
  }
  setVPC(0x10, value);
}

// 0x01:VGA, 0x03:DVI, 0x0f:DP
void setSource(uint16_t value){
  setVPC(0x60, 0x03);
}

// true:on, false:suspend
void setPower(bool value){
  if (value){
    setVPC(0xD6, 0x01);
  }
  else{
    setVPC(0xD6, 0x03);
  }
}

void loop() {
  Serial.println("\n\nsending command");   // print the reading
  //setBrightness(66);
  //setSource(0);
  setPower(true);
  delay(2000);
  setBrightness(66);
  delay(10000000000000);

}
