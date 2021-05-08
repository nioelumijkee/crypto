#!/usr/bin/env python3
# test

import sys
import ncp
import prn
import rnd

# ---------------------------------------------------------------------------- #
# parse arguments
src = ''
st = 0
le = 0

try:
    src = sys.argv[1]
    src = src.encode('utf-8')
    st  = int(sys.argv[2])
    le  = int(sys.argv[3])
except:
    print('Usage: <string> <start> <len>')
    exit()

print('-'*80)
print(src)

# ---------------------------------------------------------------------------- #

key = rnd.get_rnd(128)

ncp.encoder_bits(src, key, st, le)
prn.print_bytes(src, 16)

ncp.decoder_bits(src, key, st, le)
prn.print_bytes(src, 16)

usrc = src.decode('utf-8')
print('-'*80)
print(usrc)
