import serial
from time import sleep

ser = serial.Serial('/dev/ttyS0', 115200)
while True:
    message = ser.read(8)
    print(message);
    sleep(1)