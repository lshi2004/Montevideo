#!/usr/bin/env python
import array

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
   # @return a ListNode
   def wordBreak(self, s, dict):
       length = len(s) + 1
       Poss = array.array('i', [0]*length)
       Poss[0] = 1

       for i in xrange(1, length) : 
           for k in xrange(0, i) :
               print "Poss[k]", k, i, Poss[k], "in dict ", s[k:i], s[k:i] in dict
               if Poss[k] == 1 and s[k:i] in dict : 
                   Poss[i] = 1
                   break 
  
       return Poss[length-1] == 1 


def printNodeList(l1) : 
   node = l1 
   while node != None : 
      print "Number:  " + repr(node.val)
      node = node.next 





if __name__ == "__main__":
   solution = Solution() 

   C1 = ListNode(3)
   C1.val = 3
   C1.next = None 

   C2 = ListNode(4)
   D1 = ListNode(4)
   C2.val = 3
   C2.next = D1 
 
   C3 = ListNode(2)
   C3.val = 2
   C3.next = C2
   

   D1.val = 4
   D1.next = C3 

   D2 = ListNode(6)
   D2.val = 6
   D2.next = D1
 
   D3 = ListNode(5)
   D3.val = 5
   D3.next = D2
   myDict = { 
       'Leet': 'Hello', 
       'Code': 'Test', 
       'How': 'My',
   } 
   	 
   hasCycle = solution.wordBreak("LeetCode", myDict) 

   print "Returned ", repr(hasCycle) 

#accepted 05/02/2014


      
