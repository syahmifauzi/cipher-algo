#!/usr/bin/env python

import sys

def ceasar(rot, text):
  ABC = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
  abc = 'abcdefghijklmnopqrstuvwxyz'
  res = ''
  for ch in text:
    if ch >= 'A' and ch <= 'Z':
      res += ABC[(ord(ch)-ord('A')+rot) % 26]
    elif ch >= 'a' and ch <= 'z':
      res += abc[(ord(ch)-ord('a')+rot) % 26]
    else:
      res += ch
  return res

if len(sys.argv) != 3:
  print 'Usage: ./ceasar.py <rot> <text>'
  print 'Example: ./ceasar.py 3 "SyAhmi Fauzi"'
else:
  rot = int(sys.argv[1])
  text = sys.argv[2]
  print ceasar(rot, text)
