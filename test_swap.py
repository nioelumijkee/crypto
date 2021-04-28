#!/usr/bin/env python3
# test

import sys
import ncp
import prn

# ---------------------------------------------------------------------------- #
# parse arguments
src = ''
a = 1
b = 1
c = 1

try:
    src = sys.argv[1]
    a = int(sys.argv[2])
    b = int(sys.argv[3])
    c = int(sys.argv[4])
except:
    print('Usage: <string> <a> <b> <c>')
    exit()

print('-'*80)
print(src)

# ---------------------------------------------------------------------------- #
src = src.encode('utf-8')

ncp.encoder_swap(src, a, b, c)
prn.print_bytes(src, 16)

ncp.decoder_swap(src, a, b, c)
prn.print_bytes(src, 16)

usrc = src.decode('utf-8')
print('-'*80)
print(usrc)
