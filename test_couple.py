#!/usr/bin/env python3
# test

import sys
import ncp
import prn

# ---------------------------------------------------------------------------- #
# parse arguments
src = ''

try:
    src = sys.argv[1]
except:
    print('Usage: <string>')
    exit()

print('-'*80)
print(src)

# ---------------------------------------------------------------------------- #
src = src.encode('utf-8')

key = ncp.gen_blend256()

ncp.deencoder_couple(src, key)
prn.print_bytes(src, 16)

key = ncp.gen_blend256_invert(key)

ncp.deencoder_couple(src, key)
prn.print_bytes(src, 16)

usrc = src.decode('utf-8')
print('-'*80)
print(usrc)
