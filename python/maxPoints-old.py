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
       result = 0
       for B in points: 
           line_index = dict() 
           index = points.index(B) 
           for i in range(0, len(points)-1) :
               if i == index: 
                   continue
               A = points[i]
               if A.x - B.x == 0: 
                   slide = sys.maxint 
               else: 
                   slide = 1.0*(A.y -B.y)/(A.x - B.x) 
               
               if slide in line_index: 
                  line_index[slide] += 1
                  print repr(A) + " ---  " + repr(B)
               else: 
                  line_index[slide] = 1

               print "Result is " + repr(line_index[slide])
               
               max = 0
               for key in line_index:
                   if max < line_index[key]: 
                       max = line_index[key]
               if max > result:
                   result = max   
            
       return result


if __name__ == "__main__":
   solution = Solution() 
   PA0 = Point(1,1)
   PA1 = Point(2,2)
   PA2 = Point(3,3) 
   PA3 = Point(3,5) 

#   points = [PA0, PA1, PA2, PA3]  


   print "Hello "+ repr(solution.maxPoints(points))+" World"

#linear runtime complexity needed!!!



       
