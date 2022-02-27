import serial
from time import sleep

ser = serial.Serial('/dev/ttyS0', 115200, timeout=1)

ser.write(bytes("#s100%", "utf-8"))
