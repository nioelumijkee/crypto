#!/usr/bin/env python3

import ncp
import rnd
import random

# ---------------------------------------------------------------------------- #
def test(itt):
    for i in range(itt):
        size_src  = random.randint(-10000, 10000)
        size_key  = random.randint(-10000, 10000)
        st        = random.randint(-10000, 10000)
        le        = random.randint(-10000, 10000)
        try:
            src = rnd.get_rnd(size_src)
            key = rnd.get_rnd(size_key)

            h0 = ncp.hash_r(src, 16)

            ncp.encoder_bits(src, key, st, le)
            ncp.decoder_bits(src, key, st, le)

            h1 = ncp.hash_r(src, 16)
            if h0 == h1:
                print('[%4d] %8d %8d %8d %8d - test bits - ok' % (
                    i, size_src, size_key, st, le))
            else:
                print('[%4d] %8d %8d %8d %8d - test bits - hash !=' % (
                    i, size_src, size_key, st, le))
                return(1)
        except:
            print('[%4d] %8d %8d %8d %8d - test bits -error' % (
                i, size_src, size_key, st, le))
            return(1)
    return(0)
