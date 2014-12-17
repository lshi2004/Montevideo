#!/usr/bin/env python
import string 

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    # @return a boolean
    def isPalindrome(self, x):
        if x < 0 : 
            return False 
        div = 1
        while x / div >= 10: 
            div *= 10 
        
        print "div ", div 
 
        while x > 0 : 
            ll = x / div 
            rr = x % 10 
            print "ll rr div x ", ll, rr , div, x 
            if ll != rr : 
               return False 
            x = x % div / 10 
            div /= 100

        return True


def printNodeList(l1) : 
   node = l1 
   while node != None : 
      print "Number:  " + repr(node.val)
      node = node.next 





if __name__ == "__main__":
   solution = Solution() 

   hasCycle = solution.isPalindrome(10000021) 

   if hasCycle : 
       print "Has Cycle "
   else : 
       print "Does not have Cycle "

#accepted 05/12/2014


      
