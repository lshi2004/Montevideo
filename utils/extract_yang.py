#!/usr/bin/env python 
import re 
import sys 
import urllib2 

if len(sys.argv) != 2: sys.exit(0)

content = 'dyang'
sequence = 0 
fd = None 


def is_separator(line): 
  if re.search("Internet-Draft", line): return 0
  if re.search("Expires", line): return 0
  if re.search("Standard Track", line): return 0 
  return 1

response = urllib2.urlopen(sys.argv[1])  

#for line in response: 
#  print line
#sys.exit(0)

#with open(sys.argv[1]) as f: 
for line in response: 
    if re.search('CODE BEGINS', line): 
      sequence += 1 
      fd = open(content + str(sequence), 'w')
    elif re.search('CODE ENDS', line): 
      fd.close()
      fd = None 
    else: 
      if fd and is_separator(line): 
        fd.write(line)

        
print "Total " + str(sequence) + " Files Written \n"
 

