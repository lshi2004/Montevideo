#!/usr/bin/env python


class Solution:
    # @param s, a string
    # @return a string
    def reverseWords(self, s):
       import string 
       s1 = string.split(s)
       s1.reverse()
       return string.join(s1)


if __name__ == "__main__":
   solution = Solution() 
   print "Hello"+solution.reverseWords("")+"World"

#accepted 05/02/2014


       
