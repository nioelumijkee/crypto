#!/usr/bin/env python3
# test crypt.so

import random
import ncp
import rnd

# ---------------------------------------------------------------------------- #
def test(itt):
    for i in range(itt):
        size_src  = random.randint(-10000, 10000)
        size_hash = random.randint(-10000, 10000)
        try:
            src = rnd.get_rnd(size_src)
            h = ncp.hash_r(src, size_hash)
            print('[%4d] %8d %8d - test hash - hash len %d' % (
                i, size_src, size_hash, len(h)))
        except:
            print('[%4d] %8d %8d - test hash - error' % (
                i, size_src, size_hash))
            return(1)
    return(0)

