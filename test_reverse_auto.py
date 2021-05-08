#!/usr/bin/env python3

import ncp
import rnd
import random

# ---------------------------------------------------------------------------- #
def test(itt):
    for i in range(itt):
        size_src  = random.randint(-10000, 10000)
        st        = random.randint(-10000, 10000)
        le        = random.randint(-10000, 10000)
        try:
            src = rnd.get_rnd(size_src)

            h0 = ncp.hash_r(src, 16)
            
            ncp.reverse(src, st, le)
            ncp.reverse(src, st, le)

            h1 = ncp.hash_r(src, 16)
            if h0 == h1:
                print('[%4d] %8d %8d %8d - test reverse - ok' % (
                    i, size_src, st, le))
            else:
                print('[%4d] %8d %8d %8d - test reverse - hash !=' % (
                    i, size_src, st, le))
                return(1)
        except:
            print('[%4d] %8d %8d %8d - test reverse - error' % (
                i, size_src, st, le))
            return(1)
    return(0)
