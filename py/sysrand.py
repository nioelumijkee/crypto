#!/usr/bin/env python3
# make random bytes with SystemRandom

import sys
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
# print size, random
def print_rand(r):
    print('-'*80)
    print(type(r))

    r = r.decode('utf-8')
    print(r)

    print('-'*80)
    for i in range(len(r)): # --------- fuck this ------------------------vvv
        s = r[i]
        s = ord(s)
        s = ("%s" % (hex(s)[2:])).upper()
        if len(s) == 1:
            s = '0' + s
        print(s , end=' ')
        if i % 16 == 15:
            print("")
    print("") # ----------------------------------------------------------^^^

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

# ---------------------------------------------------------------------------- #
# for example
def main():
    if len(sys.argv) < 2:
        size = 256
    else:
        try:
            size = int(sys.argv[1])
            if size < 1:
                size = 1
        except:
            size = 256
    print("size", size)

    init_sysrand_by_time()
    r = get_rand(size)
    print_rand(r)

# ---------------------------------------------------------------------------- #
if __name__ == "__main__":
    main()
