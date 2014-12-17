#!/usr/bin/env python


class Solution:
    # @param s, a string
    # @return a string
    def evalRPN(self, tokens):
       stack = []
       for op in tokens: 
           if op.isdigit() or (op.startswith('-') and len(op) > 1) : 
              stack.append(int(op))
           else: 
              if len(stack) < 2: 
                 break  
              op1 = stack.pop()
              op2 = stack.pop()

              if op == '+':
                 stack.append(op2+op1)
                 print repr(op2) + " + " + repr(op1) 

              if op == '-':
                 stack.append(op2-op1)
                 print repr(op2) + " - " + repr(op1) 

              if op == '*':
                 stack.append(op2*op1)
                 print repr(op2) + " * " + repr(op1) 
 
              if op == '/':
                 sign = 1
                 if (op2 < 0): 
                    sign *= -1
               
                 if (op1 < 0): 
                    sign *= -1
                 stack.append(sign*op2//op1*sign)
                 print repr(op2) + " / " + repr(op1) 

       if len(stack) != 1: 
          return 0

       return stack.pop() 


if __name__ == "__main__":
   solution = Solution() 
#   print solution.evalRPN( ["2", "1", "+", "3", "*"])
#   print solution.evalRPN( ["4", "-100", "5", "/", "+"])
#   print solution.evalRPN(["10","6","9","3","+","-11","*","/","*","17","+","5","+"] )

   print solution.evalRPN(["4","-2","/","2","-3","-","-"] )

#
#accepted 05/02/2014
#python 2.7 / negative number 
# 
#

       
