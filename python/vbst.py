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
    def validBST(self, root, MMIN, MMAX) :
        if root == None: 
            return True
        
        if root.val < MMAX and root.val > MMIN :
              return self.validBST(root.left, MMIN, root.val) and self.validBST(root.right, root.val, MMAX) 
        
        return False
             
        
    # @param root, a tree node
    # @return a boolean
    def isValidBST(self, root):
      #  return self.validBST(root, -sys.maxint, sys.maxint)
      return self.validBST(root, -2**32, 2**32)
        


if __name__ == "__main__":
   solution = Solution() 


   D1 = TreeNode(3) 
   D2 = TreeNode(4) 
   D3 = TreeNode(5) 
   
   hasCycle = solution.isValidBST(D1)  

   if hasCycle : 
       print "Has Cycle ", hasCycle
   else : 
       print "Does not have Cycle "

#accepted 05/13/2014


      
