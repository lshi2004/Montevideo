#!/usr/bin/env python
import string
import sys


# Definition for a  binary tree node
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    # @param    A       a list of integers
    # @param    elem    an integer, value need to be removed
    # @return an integer
    def removeElement(self, A, elem):
        start = 0
        end = len(A) - 1
           
        while start <= end :
            
            while start <= end and A[end] == elem :
                end -= 1
                A.pop()
   
            while start<= end and A[start] != elem:
                start += 1
               
            if start < end:  
                temp = A[start] 
                A[start] = A[end] 
                A[end] = temp
 

        return A  

if __name__ == "__main__":
   solution = Solution() 


   D1 = TreeNode(3) 
   D2 = TreeNode(4) 
   D3 = TreeNode(5) 
   
   hasCycle = solution.removeElement([3, 0, 0, 4, 0, 5, 0 ], 0 )  
   print "Result  ", hasCycle
   hasCycle = solution.removeElement([3, 3 ], 3 )  
   print "Result  ", hasCycle
   hasCycle = solution.removeElement([2 ], 3 )  
   print "Result  ", hasCycle
   hasCycle = solution.removeElement([ ], 0 )  
   print "Result  ", hasCycle
   hasCycle = solution.removeElement([3, 4, 4, 3, 4 ], 3 )  
   print "Result  ", hasCycle


#accepted 05/13/2014


#        i = 0
#        j = 0
#        while j < len(A) : 
#            if A[j] != elem : 
#               A[i] = A[j]
#               i += 1
#            j += 1
#
#        return i    
# 
