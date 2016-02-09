from CloudIterator import *
import math

'''
This class stores what the map and allows methods to be applied to the map. 
'''
class PointMap:

        
    def pointCloudToPointArray(self, pointCloud, rezolution):
        
        robotOdom = 0#todo fill with robot odom
        xMin = -1#todo calc x min
        xMax = 1#todo calc x max
        yMin = -1#todo calc y min
        yMax = 5#todo calc y max
        arrayMap = []
        for x in range(int(round((xMax - xMin)/rezolution)) + 1):
            column = []
            for y in range(int(round((yMax- yMin)/rezolution)) + 1):
                column.append(None)
            arrayMap.append(column)
            point = pointCloud.getPoint()
        while(point != None):
            if((point[0] > xMin) and (point[0] < xMax) and (point[2] > yMin) and (point[2] < yMax)):#rotate point based on robot transform
                stack = arrayMap[int(round((point[0] - xMin) / rezolution))][int(round((point[2] - yMin)  / rezolution))]
                print stack
                if(arrayMap[int(round((point[0] - xMin) / rezolution))][int(round((point[2] - yMin)  / rezolution))] == None):
                
                    arrayMap[int(round((point[0] - xMin) / rezolution))][int(round((point[2] - yMin) / rezolution))] = [].append(-1 * point[1])
                    #print arrayMap[int(round((point[0] - xMin) / rezolution))][int(round((point[2] - yMin) / rezolution))]
                    print [].append([(-1*point[1])])
                else:
                    arrayMap[int(round((point[0] - xMin) / rezolution))][int(round((point[2] - yMin) / rezolution))].append(-1 * point[1])
            point = pointCloud.getPoint()
        #print arrayMap
        return arrayMap
    def __init__(self, pointCload, rezolution):
        self.rezolution = rezolution
        self.pointArray = self.pointCloudToPointArray(pointCload, rezolution)        
        
    def heightMap(self):
        x = 0
        zClearance = 1
        heightMap = []
        for x in range(len(self.pointArray)):
            column = []
            for y in range(len(self.pointArray[0])):
                column.append(None)
            heightMap.append(column)
        for xCol in self.pointArray:
            y = 0
            for zlist in xCol:
                if(zlist != None):
                    zlist.sort
                    zBottom = 0
                    zLast = None
                    for z in zlist:
                        if(zLast != None):
                            if(z - zlast > zClearance):
                                zBottom = zlast
                        else:
                            zLast = z
                        if(zLast > 0):
                            break
                    heightMap[x][y] = zBottom
                else:
                    heightMap[x][y] = -10#change
            y += 1
        x += 1
        
        return heightMap
    def obstacleMap(self):
        MaxSlope = 1# fill with walrus max slope
        heightMap = self.heightMap()
        obstacleMap = []
        for x in range(len(heightMap)):
            column = []
            for y in range(len(heightMap[0])):
                column.append(None)
            obstacleMap.append(column)
        for x in range(len(heightMap)):
            for y in range(len(heightMap[0])):

                rezX = 2
                if x == 0:
                    negX = heightMap[x][y]
                    RezX = 1
                else:
                    negX = heightMap[x-1][y]

                if x == (len(heightMap)-1):
                    posX = heightMap[x][y]
                    rezX = 1
                else:
                    posX = heightMap[x+1][y]

                rezY = 2
                if y == 0:
                    negY = heightMap[x][y]
                    rezY = 1
                else:
                    negY = heightMap[x][y-1]

                if y == (len(heightMap[0])-1):
                    posY = heightMap[x][y]
                    rezY = 1
                else:
                    posY = heightMap[x][y+1]
                if posX == None or negX == None or posY == None or negX == None:
                    obstacleMap[x][y] = False
                elif abs((posX - negX)/(rezX * self.rezolution)) > MaxSlope or abs((posY - negY)/(rezY * self.rezolution)) > MaxSlope:
                    obstacleMap[x][y] = True
                else:
                    obstacleMap[x][y] = False
        return obstacleMap

