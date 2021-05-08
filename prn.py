#!/usr/bin/env python3

# ---------------------------------------------------------------------------- #
# arg: bytes width
# print size, random
def print_bytes(data, width):

    print('-'*80)
    print('size: %d' % (len(data)))

    j = 0

    size = len(data)

    p0 = width * 2
    p1 = size % width
    if p1 == 0:
        p1 = width
    p1 += width
    p1 = size - p1

    # symbols
    print('.'*80)
    skip = 0
    for i in range(size):
        s = data[i]

        if i < p0:
            view = 1
        elif i >= p1:
            view = 1
        else:
            view = 0

        if i >= p0 and i < p1 and skip == 0:
            skip = 1
            print('---')

        if view:
            if s >= 33 and s <= 126:
                s = "%s " % (chr(s))
                print(s, end=' ')
            else:
                s = "  "
                print(s, end=' ')

            if i % width == width - 1:
                print("")

    if i % width != width - 1:
        print("")


    # numbers hex
    print('.'*80)
    skip = 0
    for i in range(size):
        s = data[i]

        if i < p0:
            view = 1
        elif i >= p1:
            view = 1
        else:
            view = 0

        if i >= p0 and i < p1 and skip == 0:
            skip = 1
            print('---')

        if view:
            s = ("%s" % (hex(s)[2:])).upper()
            if len(s) == 1:
                s = '0' + s
            print(s , end=' ')
            if i % width == width - 1:
                print("")

    if i % width != width - 1:
        print("")
