// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// BH1715
// This code is designed to work with the BH1715_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Light?sku=BH1715_I2CS#tabs-0-product_tabset-2

#include<application.h>
#include<spark_wiring_i2c.h>

// BH1715 I2C address is 0x23(35)
#define Addr 0x23

int luminance = 0;
void setup()
{
    // Set variable
    Particle.variable("i2cdevice","BH1715");
    Particle.variable("luminance",luminance);
  
    // Initialise I2C communication as MASTER
    Wire.begin();
    // Initialise serial communication, set baud rate = 9600
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
    unsigned int data[2];
  
    // Request 2 byte of data
    Wire.requestFrom(Addr, 2);

    // Read 2 bytes of data
    // ALS msb, ALS lsb
    if(Wire.available()==2) 
    {
      data[0] = Wire.read();
      data[1] = Wire.read();
    }
    delay(300);
    
    // Convert the data
    luminance = ((data[0] & 0xFF) * 256 + (data[1] & 0xFF)) / 1.20;
        
    // Output data to dashboard
    Particle.publish("Ambient Light Luminance   :", String(luminance));
}

