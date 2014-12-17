#!/usr/bin/env python
import string 

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    # @return an integer
    def reverse(self, x):
        if x < 0 : 
           sign = -1
           x = -x 
        else : 
           sign = 1

        
        num = 0
        while x > 0 : 
           num = num * 10 + x % 10
           x = x / 10
           
        return num*sign         

def printNodeList(l1) : 
   node = l1 
   while node != None : 
      print "Number:  " + repr(node.val)
      node = node.next 





if __name__ == "__main__":
   solution = Solution() 

   hasCycle = solution.reverse(-123) 

   if hasCycle : 
       print "Has Cycle ", hasCycle
   else : 
       print "Does not have Cycle "

#accepted 05/13/2014


      
