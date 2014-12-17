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
   # @param A, a list of integer
    # @return an integer
    def singleNumber(self, A):
        bit = [0 for i in xrange(32)]
     
        for i in range(32): 
            for x in A  :
                if x & (1 << i) == 1 << i : 
                    bit[i] += 1
        sum = 0   
        if bit[31] % 3 == 0 : 
            for i in xrange(31): 
                if bit[i] % 3 == 1: sum += 1 << i 
        else: 
            for i in xrange(31): 
                if bit[i] % 3 == 0: sum += 1 << i 
            sum = - (sum+1) 
            
        return sum
        

if __name__ == "__main__":
   solution = Solution() 


   D1 = TreeNode(3) 
   D2 = TreeNode(4) 
   D3 = TreeNode(5) 
   
   hasCycle = solution.singleNumber([0, 0, 0, 5 ])  

   if hasCycle : 
       print "Has Cycle ", hasCycle
   else : 
       print "Does not have Cycle "

#accepted 05/13/2014


      
