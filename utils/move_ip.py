#!/usr/bin/env python 
import re 
import sys 

if len(sys.argv) != 2: sys.exit(0)

content = '' 
with open(sys.argv[1]) as f: 
  for line in f: 
    if re.search('no ip access', line): print line
    else: content = content + line 

print content 

