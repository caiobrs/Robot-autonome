from dis import dis
import math
import sqlite3

from numpy import mat
import matplotlib.pyplot as plt
import pandas as pd
import networkx as nx

dataWithoutObstacles = {
    0: [0.0, 2.0, [1, 3]],
    1: [0.0, 1.0, [0, 2, 4]],
    2: [0.0, 0.0, [1, 5]],
    3: [1.0, 2.0, [0, 4, 6]],
    4: [1.0, 1.0, [1, 3, 5, 7]],
    5: [1.0, 0.0, [2, 4, 8]],
    6: [2.0, 2.0, [3, 7]],
    7: [2.0, 1.0, [4, 6, 8]],
    8: [2.0, 0.0, [5, 7]],
}

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

def plotAllCoordinates(graph) :
    networks = []
    positions = {i:(graph[i][0],graph[i][1]) for i in list(graph.keys())}
    for source in graph :
        for goal in graph[source][2] :
            if (goal > source) :
                networks.append((source, goal))
    
    G_1 = nx.Graph()
    G_1.add_edges_from(networks)

    nx.draw(G_1, positions, with_labels = True)

    plt.show()
    

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

def plotGraph(posX, posY, path) :
    plt.scatter(posX,posY)
    plt.plot(posX,posY)
    for i, p in enumerate(path):
        plt.annotate(p,(posX[i]+0.02,posY[i]+0.02))
    plt.show()

plotAllCoordinates(dataWithoutObstacles)

plotAllCoordinates(data)

dist, prev = dijkstra(data, nodeBegin)

path = getPath(prev, nodeBegin, nodeGoal)

coordinates = getCoordinates(data, path)

x = [x[0] for x in coordinates]
y = [x[1] for x in coordinates]

plotGraph(x, y, path)