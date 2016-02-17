from CloudIterator import *
import math

class PointMap:
    def __init__(self, pointCload, rezolution):
        self.rezolution = rezolution
        self.pointArray = self.pointCloudToPointArray(pointCload, rezolution)     
        
    def pointCloudToPointArray(self, pointCloud, rezolution):
        
        robotOdom = 0#todo fill with robot odom
        xMin = -1#todo calc x min
        xMax = 1#todo calc x max
        yMin = -1#todo calc y min
        yMax = 5#todo calc y max
        zMax = .5
        zMin = -.2
        arrayMap = []
        for x in range(int(round((xMax - xMin)/rezolution)) + 1):
            column = []
            for y in range(int(round((yMax- yMin)/rezolution)) + 1):
                column.append(0)
            arrayMap.append(column)
            point = pointCloud.getPoint()
        while(point != None):
            if((point[0] > xMin) and (point[0] < xMax) and (point[2] > yMin) and (point[2] < yMax) and (point[1] < zMax and point[1] < zMin)):
                    arrayMap[int(round((point[0] - xMin) / rezolution))][int(round((point[2] - yMin) / rezolution))] += 1
            point = pointCloud.getPoint()
        return arrayMap
    def obstacleMap(self):
        return self.pointArray 

