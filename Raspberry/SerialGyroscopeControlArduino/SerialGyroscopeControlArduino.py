import serial
import time

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyS0', 9600, timeout=1)
    
    while True:
        try :
            ser.flushInput()
            ser.flushOutput()
            time.sleep(0.05)
            ser.write((str("#" + str(round(time.time())) + "%")).encode('utf-8'))            
            while 1 :
                if ser.inWaiting():
                    line = ser.readline().decode('utf-8').rstrip()
                    print(line)
                    
                    break
            time.sleep(0.07)
        except :
            ser = serial.Serial('/dev/ttyS0', 9600, timeout=1)