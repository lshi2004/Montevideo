#!/usr/bin/env python


# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
   # @return a ListNode
   def hasCycle(self, head):
       first = head
       second = head 
 
       while first != None : 
          first = first.next 

          if second == None or second.next == None: 
              return None
          second = second.next.next 
  
          if first == second: 
              break 

       print "Break out ", first.val 
       first = head 
       while first != second: 
            first = first.next
            second = second.next 
       print "New out ", first.val 
 
       return first 


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
   
   hasCycle = solution.hasCycle(D3) 

   if hasCycle : 
       print "Has Cycle ", hasCycle.val
   else : 
       printNodeList(D3)

#accepted 05/02/2014


      
