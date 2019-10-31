#!/usr/bin/env python

import sys

def substitution(key, text):
  KEY = key.upper()
  key = key.lower()
  res = ''
  for ch in text:
    if ch >= 'A' and ch <= 'Z':
      res += KEY[ord(ch)-ord('A')]
    elif ch >= 'a' and ch <= 'z':
      res += key[ord(ch)-ord('a')]
    else:
      res += ch
  return res

if len(sys.argv) != 3:
  print 'Usage: ./substitution.py <key> <text>'
  print 'Example: ./substitution.py "QWERTYUIOPASDFGHJKLZXCVBNM" "SyAhmi Fauzi"'
else:
  key = sys.argv[1]
  text = sys.argv[2]
  print substitution(key, text)
