#!/usr/bin/env python3
# test crypt.so

import sys
import ncryptpy
import printr

# ---------------------------------------------------------------------------- #
# parse arguments
src = ''

try:
    src = sys.argv[1]
    size = int(sys.argv[2])
except:
    print('Usage: <string> <size>')
    exit()

print('src  = ', src)
print('size = ', size)
src = src.encode('utf-8')

# ---------------------------------------------------------------------------- #
# hash_r
src = ncryptpy.hash_r(src, size)
printr.printr(src, 16)


