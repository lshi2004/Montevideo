#!/usr/bin/env python


# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
   # @return a ListNode
   def addTwoNumbers(self, l1, l2):

       x = l1.val 
       node = l1.next 
       mul = 1 
       while node != None : 
          mul *= 10 
          x = x + mul*node.val 
          node = node.next 

       print "X is " + repr(x) 


       y = l2.val 
       node = l2.next 
       mul = 1 
       while node != None : 
          mul *= 10 
          y = y + mul * node.val 
          node = node.next 

       print "Y is " + repr(y) 
       
       z = x + y

       print "Z is " + repr(z) 

       current = ListNode(z % 10) 
       current.val = z % 10
       current.next = None 
     
       z = z // 10 
       head = current 
       prev = current 
       while z > 0 : 
           current = ListNode(z % 10) 
           current.val = z % 10
           current.next = None
           prev.next  = current
           prev = current 
           z = z // 10  
  
       return head  


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
   C2.val = 4
   C2.next = C1
 
   C3 = ListNode(2)
   C3.val = 2
   C3.next = C2
   

   D1 = ListNode(4)
   D1.val = 4
   D1.next = None 

   D2 = ListNode(6)
   D2.val = 6
   D2.next = D1
 
   D3 = ListNode(5)
   D3.val = 5
   D3.next = D2
   
   E1 = solution.addTwoNumbers(C3, D3)

   printNodeList(E1)

#accepted 05/02/2014


       
