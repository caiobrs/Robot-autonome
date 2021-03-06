from marvelmind import MarvelmindHedge
from time import sleep
import time
import sys

def main():
    hedge = MarvelmindHedge(tty = "/dev/ttyACM0", adr=None, debug=False) # create MarvelmindHedge thread
    hedge.start() # start thread
    timeInit = time.time()*1000
    while True:
        try:
            sleep(0.1)
            positions = hedge.getPositionXY()
            print(positions)
            file = open('data.txt','a')
            file.write("{:.2f}".format(time.time()*1000 - timeInit)+"\t"+str(positions[0])+"\t"+str(positions[1])+"\n")
            file.close()
        except KeyboardInterrupt:
            hedge.stop()  # stop and close serial port
            sys.exit()
            
main()

