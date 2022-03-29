from dis import dis
import math
import numpy

import serial
from marvelmind import MarvelmindHedge
import sys
import time

data = {
    0: [-0.06, 1.0, [1]],
    1: [-0.06, 0.6, [0, 2]],
    2: [-0.06, 0.1, [1, 5]],
    3: [0.5, 1.0, [4, 6]],
    4: [0.5, 0.6, [3, 5, 7]],
    5: [0.5, 0.1, [2, 4]],
    6: [1.0, 1.0, [3, 7]],
    7: [1.0, 0.6, [4, 6, 8]],
    8: [1.0, 0.1, [7]],
}

marginRobot = 0.2
nodeBegin = 0
nodeGoal = 8
    

def calcDist(graph, node1, node2) :
    return math.sqrt((graph[node1][0] - graph[node2][0])**2 + (graph[node1][1] - graph[node2][1])**2)

def dijkstra(graph, source) :
    dist = [math.inf for i in range(len(data))]
    prev = [-1 for i in range(len(data))]

    dist[source] = 0

    for i in graph[source][2] :
        dist[i] = calcDist(graph, source, i)
        prev[i] = source

    Q = list(graph.keys())
    Q.remove(source)
    
    while Q :
        u = math.inf

        for i in Q :
            if (dist[i] < u) :
                u = i

        Q.remove(u)
        for i in graph[u][2] :
            distNode = calcDist(graph, u, i) + dist[u]
            if (distNode < dist[i]) :
                dist[i] = distNode
                prev[i] = u
    
    return dist, prev

def getPath (prev, source, goal) :

    path = []
    while (source != goal) :
        path.append(goal)
        goal = prev[goal]

    path.append(goal)
    return path[::-1]

def getCoordinates(graph, path) :
    coordinates = []
    for i in path :
        coordinates.append((graph[i][0], graph[i][1]))
    return coordinates

def getAngle(coordinates) :
    coordinatesAngle = []

    for i in range(1, len(coordinates)) :
        angle = 0.0
        if (coordinates[i][0] == coordinates[i - 1][0]) :
            angle = numpy.sign(coordinates[i][1] - coordinates[i - 1][1]) * 90.0
        else :
            angle = (coordinates[i][1] - coordinates[i - 1][1]) / (coordinates[i][0] - coordinates[i - 1][0])
            angle = math.atan(angle) * 360 / (2 * math.pi)
            if (coordinates[i][0] - coordinates[i - 1][0] < 0) :
                angle = 180 + angle
            
            if (angle >= 180) :
                angle = - (360 - angle)
        
        coordinatesAngle.append((*coordinates[i], angle))
    
    return coordinatesAngle

dist, prev = dijkstra(data, nodeBegin)

path = getPath(prev, nodeBegin, nodeGoal)

coordinates = getCoordinates(data, path)

coordinatesAngle = getAngle(coordinates)

print(coordinatesAngle)

hedge = MarvelmindHedge(tty = "/dev/ttyACM0", adr=None, debug=False) # create MarvelmindHedge thread
hedge.start() # start thread

index = 0
if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyS0', 9600, timeout=1)
    
    
    while True:
        try :
            ser.flushOutput()
            time.sleep(0.02) 
            positions = hedge.getPositionXY()

            targetX = coordinatesAngle[index][0]
            targetY = coordinatesAngle[index][1]
            targetTheta = coordinatesAngle[index][2]
            
            text = str(positions[0]) + " \t " + str(positions[1]) + " \n "
            
            
            if (math.sqrt((targetX - positions[0]) ** 2 + (targetY - positions[1]) ** 2) < 0.26 and index + 1 < len(coordinatesAngle)) :
                index += 1
    

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