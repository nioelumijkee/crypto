#!/usr/bin/env python3

import ncp
import prn
import rnd

# ---------------------------------------------------------------------------- #
ncp.random512_set(0)
ncp.random512()
seed = ncp.random512_get()
print("random seed 0       : ", seed)

# ---------------------------------------------------------------------------- #
ncp.random512_set(10)
ncp.random512()
seed = ncp.random512_get()
print("random seed 10      : ", seed)

# ---------------------------------------------------------------------------- #
ncp.random512_set_by_time()
ncp.random512()
seed = ncp.random512_get()
print("random seed time    : ", seed)

# ---------------------------------------------------------------------------- #
ncp.random512_set(0)
rnd.set_rnd(0)
seed = rnd.get_rnd(512)
prn.print_bytes(seed, 16)
ncp.random512_set_key(seed)
ncp.random512()
seed = ncp.random512_get()
print("random by key       : ", seed)
