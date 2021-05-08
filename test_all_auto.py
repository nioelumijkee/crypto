#!/usr/bin/env python3
# test

import test_hash_auto
import test_reverse_auto
import test_shift_auto
import test_bits_auto

itt = 1000

print('hash')
if test_hash_auto.test(itt) != 0:
    print('stop')
    exit()

print('reverse')
if test_reverse_auto.test(itt) != 0:
    print('stop')
    exit()

print('shift')
if test_shift_auto.test(itt) != 0:
    print('stop')
    exit()

print('bits')
if test_bits_auto.test(itt) != 0:
    print('stop')
    exit()


print('test complete')
