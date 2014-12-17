#!/usr/bin/env python
import sys

class Point:
    def __init__(self, a=0, b=0):
         self.x = a
         self.y = b

class Solution:
    # @param s, a string
    # @return a string
    def maxPoints(self, points):
        length = len(points)
        if length < 3: return length

        res = -1
        for i in xrange(length):
            slope = {'inf': 0}
            samePointNum = 1
            for j in xrange(length):
                if i == j: 
                    continue
                if points[i].x == points[j].x and points[i].y != points[j].y:
                    slope['inf'] += 1
                elif points[i].x != points[j].x:
                    k = 1.0 * (points[i].y - points[j].y) / (points[i].x - points[j].x)
                    slope[k] = 1 if k not in slope else slope[k] + 1
                else:
                    samePointNum += 1
                res = max(res, max(slope.values()) + samePointNum)
        return res

if __name__ == "__main__":
   solution = Solution() 
   PA0 = Point(1,1)
   PA1 = Point(2,2)
   PA2 = Point(3,3) 
   PA3 = Point(3,5) 

   points = [PA0, PA1, PA2, PA3]  


   print "Hello "+ repr(solution.maxPoints(points))+" World"

#linear runtime complexity needed!!!



       
