#!/usr/bin/env python3
# print random bytes formated

# ---------------------------------------------------------------------------- #
# arg: bytes width
# print size, random
def printr(r,w):

    print('-'*80)
    print(type(r))
    print(r)

    print('-'*80)
    for i in range(len(r)): # --------------------------------------------vvv
        s = r[i]
        s = chr(s)
        print(s , end=' ')
        if i % w == w-1:
            print("")
    print("") # ----------------------------------------------------------^^^

    print('-'*80)
    for i in range(len(r)): # --------------------------------------------vvv
        s = r[i]
        s = ("%s" % (hex(s)[2:])).upper()
        if len(s) == 1:
            s = '0' + s
        print(s , end=' ')
        if i % w == w-1:
            print("")
    print("") # ----------------------------------------------------------^^^
