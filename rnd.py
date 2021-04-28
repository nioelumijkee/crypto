#!/usr/bin/env python3
# make random bytes with SystemRandom

import random
import time

# ---------------------------------------------------------------------------- #
seed = 0

# ---------------------------------------------------------------------------- #
def set_rnd(s):
    global seed
    seed = random.SystemRandom(s)

# ---------------------------------------------------------------------------- #
def set_rnd_by_time():
    global seed
    seed = random.SystemRandom(time.time() * 10000)

# ---------------------------------------------------------------------------- #
# make random bytes
def get_rnd(size):
    k = ''
    for i in range(size):
        r = seed.random()
        r = (int(r*1000000) % 256)
        r = chr(r)
        k = "%s%s" % (k,r)
        # k = k+ord(r)
    return k.encode('utf-8')[0:size]
