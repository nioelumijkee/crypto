#!/usr/bin/env python3
# make random bytes with SystemRandom

import random
import time

# ---------------------------------------------------------------------------- #
seed = 0

# ---------------------------------------------------------------------------- #
# this make random seed by SystemRandom
def init_sysrand_by_time():
    global seed
    seed = random.SystemRandom(time.time() * 10000)

# ---------------------------------------------------------------------------- #
# this make random seed too
def init_sysrand_by_int(s):
    global seed
    seed = random.SystemRandom(s)

# ---------------------------------------------------------------------------- #
# make random bytes
def get_rand(size):
    k = ''
    for i in range(size):
        r = seed.random()
        a = int(r * 123456789)
        a = a % 256
        k = "%s%c" % (k,a)
    return k.encode('utf-8')
