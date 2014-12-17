#!/usr/bin/env python


class Solution:
    # @param s, a string
    # @return a string
    def singleNumber(self, A):
       result = []
       for num in A: 
           match = [ x for x in result if x == num ] 
           if match == [] : 
               result.append(num)
           else: 
               result.remove(num)
            
       return result.pop()


if __name__ == "__main__":
   solution = Solution() 
#   print "Hello "+ repr(solution.singleNumber([1, 2, 3, 3, 2, 4,1]))+" World"
#   print "Hello "+ repr(solution.singleNumber())+" World"

#linear runtime complexity needed!!!



       
