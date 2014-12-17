#!/usr/bin/env python
import string 

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    def opposite(self, stack, j):
        if len(stack) == 0 : 
           return False
   
        hhs = { }  
        hhs[')'] = '('
        hhs['}'] = '{'
        hhs[']'] = '['

        k = stack[-1] 
        if k == hhs[j] : 
            return True

        return False 


    # @return a boolean
    def isValid(self, s):
        stack = [ ] 
        for i, j in enumerate(s) : 
            if j in "([{)}]": 
               if j in ")}]" and self.opposite( stack, j):
                   stack.pop()
               else: 
                   stack.append(j)
 
        return len(stack) == 0 

#        if len(stack) == 0: 
#             return True
#        else: 
#             return False 
            

def printNodeList(l1) : 
   node = l1 
   while node != None : 
      print "Number:  " + repr(node.val)
      node = node.next 





if __name__ == "__main__":
   solution = Solution() 

   hasCycle = solution.isValid(" [ { } ] " )  

   if hasCycle : 
       print "Has Cycle ", hasCycle
   else : 
       print "Does not have Cycle "

#accepted 05/12/2014


      
