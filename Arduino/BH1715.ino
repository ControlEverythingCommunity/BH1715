// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// BH1715
// This code is designed to work with the BH1715_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Light?sku=BH1715_I2CS

#include <Wire.h>

// BH1715 I2C address is 0x23(35)
#define Addr 0x23

void setup()
{
	// Initialise I2C communication as MASTER
	Wire.begin();
	// Initialise Serial Communication, set baud rate = 9600
	Serial.begin(9600);

	// Start I2C Transmission
	Wire.beginTransmission(Addr);
	// Send power on command
	Wire.write(0x01);
	// Stop I2C Transmission
	Wire.endTransmission();

	// Start I2C Transmission
	Wire.beginTransmission(Addr);
	// Send continuous measurement command
	Wire.write(0x10);
	// Stop I2C Transmission
	Wire.endTransmission();
	delay(300);
}

void loop() 
{
	// Request 2 byte of data
	Wire.requestFrom(Addr, 2);

	// Read 2 bytes of data
	// ALS msb, ALS lsb
	if(Wire.available() == 2) 
	{
		data[0] = Wire.read();
		data[1] = Wire.read();
	}
  delay(300);
  
	//convert the data
	float luminance = ((data[0] * 256) + data[1]) / 1.20;
  
  // Output data to serial monitor
	Serial.print("Ambient Light Luminance 	:");
	Serial.print(luminance);
	Serial.println(" lux"); 
	}
}

