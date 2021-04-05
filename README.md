# DDC/CI VCP library
This is an Arduino library for controlling external computer monitors over the VESA DDC/CI standard. This standard is present on many different types of connectors but depends heavily on the actual manufacturer to implement it properly. Check if your setup is actually compatible with this.

# Examples
Some simple examples can be found in the examples directory.

# Functionality
- setting and reading brightness
- setting and reading power status
- setting and reading input source
- custom VCP commands

More Functionality can easily be added. See [ddcutil](https://www.ddcutil.com/vcpinfo_output/) for some further reference on VPC codes.

# Connector
The Arduino is to be connected to VGA, HDMI or DVI using the corresponding pins for DDC. This is essentially an I2C connection and uses the standard arduino Wire library so use the appropriate pins for I2C on your microcontroller.

Disclaimer: I only tested this with a VGA connection, however DVI and HDMI should work as well. Pay attention to using the correct voltages though!

## VGA
- Pin 15: DDC Clock (SCL)
- Pin 12: DDC Data (SDA)

## DVI
- Pin 6: DDC clock (SCL)
- Pin 7: DDC Data (SDA)

## HDMI
- Pin 15: DDC Clock (SCL)
- Pin 16: DDC Data (SDA)

