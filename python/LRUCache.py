#!/usr/bin/env python
import collections 

class LRUCache:

    # @param capacity, an integer
    def __init__(self, capacity):
        self.capacity = capacity 
        self.current_num = 0         
        self.cache = collections.OrderedDict() 

    # @return an integer
    def get(self, key):
        try: 
            value = self.cache[key] 
            del self.cache[key]
            self.cache[key] = value 
            return value
        except: 
            return -1 

    # @param key, an integer
    # @param value, an integer
    # @return nothing
    def set(self, key, value):
        try : 
            del self.cache[key]             
            self.cache[key] = value 
        except: 
            if self.current_num == self.capacity: 
                self.cache.popitem(last = False)
                self.current_num -= 1
            self.cache[key] = value
            self.current_num += 1 
                 





if __name__ == "__main__":
   solution = LRUCache(10) 

   solution.set(10, 20) 
   solution.set(11, 222) 
   solution.set(12, 30) 
   solution.set(13, 40) 
   solution.set(14, 50) 

   print solution.get(13)



#accepted 05/02/2014


       
