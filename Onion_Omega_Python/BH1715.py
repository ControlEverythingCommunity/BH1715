# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# BH1715
# This code is designed to work with the BH1715_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Light?sku=BH1715_I2CS#tabs-0-product_tabset-2

from OmegaExpansion import onionI2C
import time

# Get I2C bus
i2c = onionI2C.OnionI2C()

# BH1715 address, 0x23(35)
# Send power on command
#		0x01(01)	Power On
value = [0x01]
i2c.write(0x23, value)
# BH1715 address, 0x23(35)
# Send continuous measurement command
#		0x10(16)	Set Continuous high resolution mode, 1 lux resolution, Time = 120ms
value = [0x10]
i2c.write(0x23, value)

time.sleep(0.5)

# BH1715 address, 0x23(35)
# Read data back, 2 bytes
# luminance MSB, luminance LSB
data = i2c.readBytes(0x23, 0x00, 2)

# Convert the data
luminance = (data[0] * 256 + data[1]) / 1.2

# Output data to screen
print "Ambient Light luminance : %.2f lux" %luminance
