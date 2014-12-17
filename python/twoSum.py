#!/usr/bin/env python
import string 

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    # @return a tuple, (index1, index2)
    def twoSum(self, num, target):
        hash_map = dict()
        for i, j in enumerate(num) : 
            hash_map[j] = i 
            
        for i,j  in enumerate(num) : 
            v = target - j
            if v in hash_map:
               d = hash_map[v] 
               if d == i: 
                  continue  
               print "H ", i, j, v, hash_map[v] 
               return [i, hash_map[v]]
    
        return None 
         

def printNodeList(l1) : 
   node = l1 
   while node != None : 
      print "Number:  " + repr(node.val)
      node = node.next 





if __name__ == "__main__":
   solution = Solution() 

   hasCycle = solution.twoSum([3, 2, 4], 6)  

   if hasCycle : 
       print "Has Cycle ", hasCycle
   else : 
       print "Does not have Cycle "

#accepted 05/12/2014


      
