#!/usr/bin/env python3
# print bytes formated

# ---------------------------------------------------------------------------- #
# colors
col_red     = '\x1b[31m'
col_green   = '\x1b[32m'
col_yellow  = '\x1b[33m'
col_blue    = '\x1b[34m'
col_off     = '\x1b[0m'

# ---------------------------------------------------------------------------- #
# arg: bytes width
# print size, random
def print_bytes(r,w):

    print('-'*80)
    # print(r)

    # print('.'*80)
    for i in range(len(r)): # --------------------------------------------vvv
        s = r[i]

        if s >= 33 and s <= 126:
            s = "%s%s " % (col_off,chr(s))
            # s = "%s " % (chr(s))
            print(s, end=' ')
        else:
            s = "%s. " % (col_blue)
            # s = "� "
            print(s, end=' ')

        if i % w == w-1:
            print("")
    if i % w != w-1:
        print("")    # ---------------------------------------------------^^^
    print(col_off, end=' ')

    print('.'*80)
    for i in range(len(r)): # --------------------------------------------vvv
        s = r[i]
        s = ("%s" % (hex(s)[2:])).upper()
        if len(s) == 1:
            s = '0' + s
        print(s , end=' ')
        if i % w == w-1:
            print("")
    if i % w != w-1:
        print("")    # ---------------------------------------------------^^^


