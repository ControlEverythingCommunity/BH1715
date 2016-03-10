// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// BH1715
// This code is designed to work with the BH1715_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Light?sku=BH1715_I2CS#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class BH1715
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, BH1715 I2C address is 0x23(35)
		I2CDevice device = bus.getDevice(0x23);

		// Send power on command
		device.write((byte)0x01);
		// Send continuous measurement command
		device.write((byte)0x10);
		Thread.sleep(500);

		// Read 2 bytes of data
		// luminance msb, luminance lsb
		byte[] data = new byte[2];
		device.read(data, 0, 2);

		// Convert data
		double luminance = ((data[0] & 0xFF) * 256 + (data[1] & 0xFF)) / 1.20;

		// Output data to screen
		System.out.printf("Ambient Light Luminance : %.2f lux %n", luminance);
	}
}
