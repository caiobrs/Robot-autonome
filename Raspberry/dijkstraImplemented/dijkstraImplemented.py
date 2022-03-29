from dis import dis
import math
import numpy

from numpy import mat

data = {
    0: [0.0, 2.0, [1]],
    1: [0.0, 1.0, [0, 2]],
    2: [0.0, 0.0, [1, 5]],
    3: [1.0, 2.0, [4, 6]],
    4: [1.0, 1.0, [3, 5, 7]],
    5: [1.0, 0.0, [2, 4]],
    6: [2.0, 2.0, [3, 7]],
    7: [2.0, 1.0, [4, 6, 8]],
    8: [2.0, 0.0, [7]],
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

    for i in range(len(coordinates) - 1) :
        angle = 0.0
        if (coordinates[i + 1][0] == coordinates[i][0]) :
            angle = numpy.sign(coordinates[i + 1][1] - coordinates[i][1]) * 90.0
        else :
            angle = (coordinates[i + 1][1] - coordinates[i][1]) / (coordinates[i + 1][0] - coordinates[i][0])
            angle = math.atan(angle) * 360 / (2 * math.pi)
        print(angle)

dist, prev = dijkstra(data, nodeBegin)

path = getPath(prev, nodeBegin, nodeGoal)

coordinates = getCoordinates(data, path)

print(coordinates)
getAngle(coordinates)