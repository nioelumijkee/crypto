#!/usr/bin/env python3
# test crypt.so

import sys
import ncp
import prn

# ---------------------------------------------------------------------------- #
# parse arguments
src = ''
size = 0

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
h = ncp.hash_r(src, size)
prn.print_bytes(h, 16)


