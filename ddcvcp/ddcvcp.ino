#include <Wire.h>
void setup() {

  Wire.begin();                // join i2c bus (address optional for master)

  Serial.begin(9600);          // start serial communication at 9600bps
  delay(2000);
}

byte i2c_port = 0x37; //0x6E>>1


// op: VCP opcode. Can be found with ddc capabilities
// value: 16bit value
void setVCP(byte op, uint16_t value) {
  Wire.beginTransmission(i2c_port);
  Wire.write(0x51);
  Wire.write(0x84);
  Wire.write(0x03);
  Wire.write(op);
  Wire.write(byte(value >> 8));
  Wire.write(byte(value));
  Wire.write((i2c_port << 1) ^ 0x51 ^ 0x84 ^ 0x03 ^ op ^ byte(value >> 8)^byte(value)); //XOR checksum. Include all bytes sent, including slave address!
  Wire.endTransmission();
}

uint16_t getVCP(byte op) {
  Wire.beginTransmission(i2c_port);
  Wire.write(0x51);
  Wire.write(0x82);
  Wire.write(0x01);
  Wire.write(op);
  Wire.write((i2c_port << 1) ^ 0x51 ^ 0x82 ^ 0x01 ^ op); //XOR checksum. Include all bytes sent, including slave address!
  Wire.endTransmission();
  delay(40);
  Wire.requestFrom(i2c_port, 12);
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

// 0-100
void setBrightness(uint16_t value) {
  if (value > 100) {
    value = 100;
  }
  setVCP(0x10, value);
}

uint16_t getBrightness() {
  return getVCP(0x10);
}


// 0x01:VGA, 0x03:DVI, 0x0f:DP
void setSource(uint16_t value) {
  setVCP(0x60, value);
}

uint16_t getSource() {
  return getVCP(0x60);
}


// true:on, false:suspend
void setPower(bool value) {
  if (value) {
    setVCP(0xD6, 0x01);
  }
  else {
    setVCP(0xD6, 0x03);
  }
}

bool getPower(){
  byte power = getVCP(0xD6);
  if (power==0x01){
    return true;
  }
  return false;
}

void loop() {
  Serial.println("\n\nsending command");   // print the reading
  //setBrightness(66);
  setPower(true);
  delay(5000);
  setSource(0x0f);
  delay(5000);
  setPower(true);
  //delay(2000);
  //setBrightness(68);
  //delay(1000);
  //Serial.println(getSource());
  delay(10000000000000);

}
