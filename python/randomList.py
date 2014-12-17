#!/usr/bin/env python


# Definition for singly-linked list with a random pointer.
 class RandomListNode:
     def __init__(self, x):
         self.label = x
         self.next = None
         self.random = None

class Solution:
    # @param head, a RandomListNode
    # @return a RandomListNode
    def copyRandomList(self, head):
       if head == None: 
          return None

       list_map = {} 
       
       first = head
       prev = None
       while first != None : 
          second = RandomListNode(first.label) 
          if first == head: 
             new_head = second 
          else: 
             prev.next = second 
          prev = second 

          list_map[first] = second 
          first = first.next 
 
       first = head
       second = new_head 
       while first != None : 
          random = list_map.get(first.random, None) 
          second.random = random
          first = first.next 
          second = second.next 
 
       return new_head   


def printNodeList(l1) : 
   node = l1 
   while node != None : 
      print "Number:  ", node.label 
      if node.next != None: 
         print "   pointer value ", node.next.label 

 
      if node.random != None: 
         print "   random value ", node.random.label 

      node = node.next 



if __name__ == "__main__":
   solution = Solution() 

   C1 = ListNode(3)
   C1.next = None 

   C2 = ListNode(4)
   D1 = ListNode(4)
   C2.next = D1 
 
   C3 = ListNode(2)
   C3.next = C2

   D1.val = 4
   D1.next = C3 

   D2 = ListNode(6)
   D2.next = D1
 
   D3 = ListNode(5)
   D3.next = D2
   
   hasCycle = solution.copyRandomList(D3) 

   if hasCycle : 
       print "Has Cycle "
   else : 
       printNodeList(D3)

#accepted 05/10/2014


      
