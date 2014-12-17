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
    def preorderTraversal(self, root):                 
        stack = []
        result = []
   
        if root == None: 
           return []
 
        stack.append(root)

        while len(stack) != 0 : 
           node = stack.pop()
           result.append(node.val) 
           print "Node value " + repr(node) 
           print "Node value val " + repr(node.val) 
           print "Node value L " + repr(node.left) 
           print "Node value R " + repr(node.right) 
           if node.right != None : 
               stack.append(node.right) 
               print "Append R" 
           if node.left != None : 
               stack.append(node.left)  
               print "Append L" 

        return result 

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


       
