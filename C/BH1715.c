// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// BH1715
// This code is designed to work with the BH1715_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Light?sku=BH1715_I2CS#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, BH1715 I2C address is 0x23(35)
	ioctl(file, I2C_SLAVE, 0x23);

	// Send power on command(0x01)
	char config[1] = {0x01};
	write(file, config, 1);
	// Send continuous measurement command(0x10)
	config[0] = 0x10;
	write(file, config, 1); 
	sleep(1);

	// Read 2 bytes of data
	// luminance msb, luminance lsb
	char data[2]={0};
	if(read(file, data, 2) != 2)
	{
		printf("Error : Input/Output error \n");
	}
	else
	{
		// Convert the data
		float luminance  = (data[0] * 256 + data[1]) / 1.20;

		// Output data to screen
		printf("Ambient Light Luminance : %.2f lux\n", luminance);
	}
}
