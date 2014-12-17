#!/usr/bin/env python
import string 

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    # @return an integer
    def threeSum(self, num):
        num.sort()  
  
        result = []  
          
        i = 0  
        while i < len(num) - 2:  
            if i > 0 and num[i] == num[i - 1]:  
                i += 1  
                continue  
              
            j = i + 1  
            k = len(num) - 1  
              
            while j < k:  
                if num[i] + num[j] + num[k] > 0:  
                    k -= 1  
                elif num[i] + num[j] + num[k] < 0:  
                    j += 1  
                else:  
                    tmp = [num[i], num[j], num[k]]  
                    result.append(tmp)  
                      
                    j += 1  
                    k -= 1  
                      
                    while j < k and num[j] == num[j - 1]:  
                        j += 1  
                    while j < k and num[k] == num[k + 1]:  
                        k -= 1  
            i += 1  
                          
        return result 

def printNodeList(l1) : 
   node = l1 
   while node != None : 
      print "Number:  " + repr(node.val)
      node = node.next 


if __name__ == "__main__":
   solution = Solution() 

   hasCycle = solution.threeSum([3, -1,-1,2 ] ) 
#   hasCycle = solution.threeSum([-1,0,1,2,-1,-4 ] ) 
#   hasCycle = solution.threeSum([7,-1,14,-12,-8,7,2,-15,8,8,-8,-14,-4,-5,7,9,11,-4,-15,-6,1,-14,4,3,10,-5,2,1,6,11,2,-2,-5,-7,-6,2,-15,11,-6,8,-4,2,1,-1,4,-6,-15,1,5,-15,10,14,9,-8,-6,4,-6,11,12,-15,7,-1,-9,9,-1,0,-4,-1,-12,-2,14,-9,7,0,-3,-4,1,-2,12,14,-10,0,5,14,-1,14,3,8,10,-8,8,-5,-2,6,-11,12,13,-7,-12,8,6,-13,14,-2,-5,-11,1,3,-6])
 
   if hasCycle : 
       print "Has Cycle ", hasCycle
   else : 
       print "Does not have Cycle "

#accepted 05/14/2014


      
