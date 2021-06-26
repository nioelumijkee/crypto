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

    # 2
    data = fi.read()
    data_out = b''
    size_data = len(data)
    size_key = 128
    key = ncp.hash_r(word.encode(), size_key)
    j = 0
    while j < size_data:
        k = j + size_key
        buf = data[j:k]
        ncp.encoder_bits(buf, key, 0, 0)
        ncp.reverse(buf, 0, 0)
        data_out = data_out + buf
        j += size_key

    # 1
    data = data_out
    data_out = b''
    size_data = len(data)
    size_key = 64
    key = ncp.hash_r(word.encode(), size_key)
    j = 0
    while j < size_data:
        k = j + size_key
        buf = data[j:k]
        ncp.encoder_bits(buf, key, 0, 0)
        ncp.reverse(buf, 0, 0)
        data_out = data_out + buf
        j += size_key


    fo.write(data_out)
    fi.close()
    fo.close()
