#!/usr/bin/env python3
# test

import sys
import ncp
import rnd

# ---------------------------------------------------------------------------- #
def encode(filename_in, filename_out, word):
    fi = None
    fo = None
    try:
        fi = open (filename_in, 'rb')
        fo = open (filename_out, 'wb')
    except:
        print('error open files')
        exit()

    data = fi.read()

    size_data = len(data)
    size_key = 64
    step_sh = 64
    sh = 16

    key = ncp.hash_r(word.encode(), 64)

    j = 0
    while j < size_data:
        k = j + size_key
        buf = data[j:k]
        ncp.encoder_bits(buf, key, 0, 0)
        # ncp.shift(buf, 0, 0, sh)
        ncp.reverse(buf, 0, 0)
        fo.write(buf)
        j += step_sh


    fi.close()
    fo.close()
