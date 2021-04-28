#!/usr/bin/env python3

import ncp
import prn
import rnd

# ---------------------------------------------------------------------------- #
rnd.set_rnd(0)

a = rnd.get_rnd(128)
prn.print_bytes(a, 16)
