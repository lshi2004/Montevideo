#!/usr/bin/env python
import string 

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    def isAlpha(self, x): 
       if x >= 'a' and x <= 'z': 
          return True
      
       if x >= 'A' and x <= 'Z': 
          return True

       if x >= '0' and x <= '9': 
          return True

       return False 
     
    def isPalindrome(self, x):
        size = len(x)
        start = 0
        end = size-1
        x = x.lower() 
 
        while start < end : 
            while (start < end)  and (self.isAlpha(x[start]) != True) : 
                start += 1
            while (start < end)  and (self.isAlpha(x[end]) != True) : 
                end -= 1
            print "Start End ", start, end 
    
            if x[start] != x[end] : 
                return False
            start += 1
            end -= 1
        
        print "Start End ", start, end 
        if start >= end : 
            return True
        else : 
            return False 

def printNodeList(l1) : 
   node = l1 
   while node != None : 
      print "Number:  " + repr(node.val)
      node = node.next 





if __name__ == "__main__":
   solution = Solution() 

   hasCycle = solution.isPalindrome("aA") 

   if hasCycle : 
       print "Has Cycle "
   else : 
       print "Does not have Cycle "

#accepted 05/02/2014


      
