import serial
from marvelmind import MarvelmindHedge
import sys
import time

hedge = MarvelmindHedge(tty = "/dev/ttyACM0", adr=None, debug=False) # create MarvelmindHedge thread
hedge.start() # start thread

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyS0', 9600, timeout=1)
    
    while True:
        try :
            ser.flushOutput()
            time.sleep(0.02) 
            positions = hedge.getPositionXY()
            targetX, targetY, targetTheta = -0.1, 1.6, 90
            ser.write((str("#Px" + ("+" if positions[0] >= 0 else "") + str(round(positions[0] * 1000)) + "%")).encode('utf-8'))  
            time.sleep(0.02)     
            ser.write((str("#Py" + ("+" if positions[1] >= 0 else "") + str(round(positions[1] * 1000)) + "%")).encode('utf-8'))  
            time.sleep(0.02)
            ser.write((str("#Tx" + ("+" if targetX * 1000 >= 0 else "") + str(round(targetX * 1000)) + "%")).encode('utf-8'))  
            time.sleep(0.02)     
            ser.write((str("#Ty" + ("+" if targetY * 1000 >= 0 else "") + str(round(targetY * 1000)) + "%")).encode('utf-8'))  
            time.sleep(0.02)
            ser.write((str("#Tt" + ("+" if targetTheta >= 0 else "") + str(round(targetTheta)) + "%")).encode('utf-8'))  
            time.sleep(0.02)     
        except :
            ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)