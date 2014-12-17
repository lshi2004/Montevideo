#!/usr/bin/env python
import collections 

# Definition for a  binary tree node
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    # @param root, a tree node
    # @return a list of integers
    def sameTree(self, p, q):                 
        if p == None and q == None: 
           return True
 
        if p == None and q != None: 
           return False
     
        if p != None and q == None: 
           return False
        
        # p and q both not null 
        if p.val != q.val: 
           return False 

        if self.sameTree(self, p.left, q.left) != True: 
           return False 
 
        if self.sameTree(self, p.right, q.right) != True: 
           return False 

        return True 
 

if __name__ == "__main__":
   solution = Solution() 

   N1 = TreeNode(1)
   N2 = TreeNode(2)
   N3 = TreeNode(3)
   N4 = TreeNode(4)

   N1.right = N2 
   N2.left = N3 

   N3.right = N4 

   root = N1

   print "root L " + repr(root.left)
   print "root R " + repr(root.right)

   print solution.preorderTraversal(N1) 



#accepted 05/02/2014


       
