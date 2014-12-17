#!/usr/bin/env python
import string 

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    # @return an integer
    def atoi(self, str):
        size = len(str) 
        if size == 0: 
            return 0 

        num = 0 

        i = 0 
        while str[i].isspace() : 
           i += 1

        sign = 1
        if str[i] == "+" : 
            i += 1
        elif str[i] == "-":
            sign = -1
            i += 1
      
        print "Sign ", sign 
 
        while i < size : 
            if str[i] >= '0' and str[i] <= '9':
                digit = ord(str[i]) - ord('0')
                print "Digit i ", digit, i 
                i += 1
                if sign == 1 : 
                    if (2147483647 -digit)/10 < num: 
                        num = 2147483647
                        break
                    else :  
                        num = num*10 + digit
                else : 
                    if (2147483648 -digit)/10 < num: 
                        num = 2147483648
                        break
                    else :  
                        num = num*10 + digit
            else : 
                break  

        print "Num ", num, i, sign  
        return sign * num 

def printNodeList(l1) : 
   node = l1 
   while node != None : 
      print "Number:  " + repr(node.val)
      node = node.next 


if __name__ == "__main__":
   solution = Solution() 

   hasCycle = solution.atoi("   -2147483648") 

   if hasCycle : 
       print "Has Cycle ", hasCycle
   else : 
       print "Does not have Cycle "

#accepted 05/13/2014


      
