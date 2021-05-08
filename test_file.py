#!/usr/bin/env python3
# test

import sys
import ncp
import prn
import test_file_encode
import test_file_decode

# ---------------------------------------------------------------------------- #
def hash(filename):
    f = open(filename, 'rb')
    data = f.read()
    prn.print_bytes_hex(ncp.hash_r(data, 16))
    f.close()

# ---------------------------------------------------------------------------- #
filename = ''
word = ''
try:
    filename = sys.argv[1]
    word     = sys.argv[2]
except:
    print('usage: <filename> <word>')
    exit()

filename_encode = filename + '.encode'
filename_decode = filename + '.decode'

hash(filename)

test_file_encode.encode(filename, filename_encode, word)
hash(filename_encode)
test_file_decode.decode(filename_encode, filename_decode, word)
hash(filename_decode)
