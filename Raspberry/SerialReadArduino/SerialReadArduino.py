import serial
import time

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB12', 9600, timeout=1)
    
    while True:
        try :        
            while 1 :
                if ser.inWaiting():
                    line = ser.readline().decode('utf-8').rstrip()
                    print(line)
                    
                    break
        except :
            ser = serial.Serial('/dev/ttyUSB12', 9600, timeout=1)
