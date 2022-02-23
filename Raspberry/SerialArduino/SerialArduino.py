import serial
from time import sleep

ser = serial.Serial('/dev/ttyS0', 9600, timeout=1)
while True:
    ser.write(bytes("#Batata%", "utf-8"))
    sleep(1)