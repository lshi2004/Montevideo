class Solution: 
  # @param s, a string
  # @return a string 
  def reverseWords(self, s): 
    return ' '.join(s.split()[::-1]) 

if __name__ == "__main__": 
  solution = Solution()

  str = solution.reverseWords("abc def")
  print str

  
