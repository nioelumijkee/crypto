#!/usr/bin/env python3

import ncp
import prn
import sys

# ---------------------------------------------------------------------------- #
src = ''
st = 0
le = 0

try:
    src = sys.argv[1]
    src = src.encode('utf-8')
    st  = int(sys.argv[2])
    le  = int(sys.argv[3])
except:
    print('usage: <str> <start> <len>')
    exit()

# ---------------------------------------------------------------------------- #
prn.print_bytes(src, 16)
ncp.reverse(src, st, le)
prn.print_bytes(src, 16)
