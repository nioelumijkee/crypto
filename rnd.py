#!/usr/bin/env python3
# make random bytes with SystemRandom

import random
import time

# ---------------------------------------------------------------------------- #
# make random bytes
def get_rnd(size):
    if  size < 1:
        return (b'')
    seed = random.SystemRandom(time.time() * 10000)
    l = []
    for i in range(size):
        r = seed.random()
        r = int(r*100000000) % 256
        l.append(r)
    return ( bytes(l) )
