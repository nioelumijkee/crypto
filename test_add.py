#!/usr/bin/env python3

import ncp
import prn
import rnd

# ---------------------------------------------------------------------------- #
ncp.random512_set(9)
ncp.random512()
seed = ncp.random512_get()
print("random seed 0       : ", seed)

# ---------------------------------------------------------------------------- #
a = ncp.gen_blend256()
b = ncp.gen_blend256_invert(a)
c = ncp.gen_blend16()
d = ncp.gen_blend16()
e = ncp.gen1024()



prn.print_bytes(a, 16)
prn.print_bytes(b, 16)
prn.print_bytes(c, 16)
prn.print_bytes(d, 16)
prn.print_bytes(e, 16)
