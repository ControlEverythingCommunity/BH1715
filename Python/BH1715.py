# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# BH1715
# This code is designed to work with the BH1715_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Light?sku=BH1715_I2CS#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# BH1715 address, 0x23(35)
# Send power on command
#		0x01(01)	Power On
bus.write_byte(0x23, 0x01)
# BH1715 address, 0x23(35)
# Send continuous measurement command
#		0x10(16)	Set Continuous high resolution mode, 1 lux resolution, Time = 120ms
bus.write_byte(0x23, 0x10)

time.sleep(0.5)

# BH1715 address, 0x23(35)
# Read data back, 2 bytes using General Calling
# luminance MSB, luminance LSB
data = bus.read_i2c_block_data (0x23, 2)

# Convert the data
luminance = (data[0] * 256 + data[1]) / 1.2

# Output data to screen
print "Ambient Light luminance : %.2f lux" %luminance
