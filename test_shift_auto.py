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
        sh        = random.randint(-10000, 10000)
        sh_inv    = 0 - sh
        try:
            src = rnd.get_rnd(size_src)

            h0 = ncp.hash_r(src, 16)

            ncp.shift(src, st, le, sh)
            ncp.shift(src, st, le, sh_inv)

            h1 = ncp.hash_r(src, 16)
            if h0 == h1:
                print('[%4d] %8d %8d %8d %8d - test shift - ok' % (
                    i, size_src, st, le, sh))
            else:
                print('[%4d] %8d %8d %8d %8d - test shift - hash !=' % (
                    i, size_src, st, le, sh))
                return(1)
        except:
            print('[%4d] %8d %8d %8d %8d - test shift - error' % (
                i, size_src, st, le, sh))
            return(1)
    return(0)
