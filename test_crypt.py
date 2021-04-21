#!/usr/bin/env python3
# test

import sys
import ncryptpy

# ---------------------------------------------------------------------------- #
# parse arguments
src = ''

try:
    src = sys.argv[1]
except:
    print('Usage: <string>')
    exit()

print(src)
src = src.encode('utf-8')

# ---------------------------------------------------------------------------- #
# caesar
print('-'*80)
print('caesar 3')

src = ncryptpy.encoder_caesar(src, 3)
print('.'*80)
print(src)

src = ncryptpy.decoder_caesar(src, 3)
print('.'*80)
print(src)

usrc = src.decode('utf-8')
print('.'*80)
print(usrc)



# caesar
print('-'*80)
print('caesar 122')

src = ncryptpy.encoder_caesar(src, 122)
print('.'*80)
print(src)

src = ncryptpy.decoder_caesar(src, 122)
print('.'*80)
print(src)

usrc = src.decode('utf-8')
print('.'*80)
print(usrc)

# ---------------------------------------------------------------------------- #
# affine
print('-'*80)
print('affine 3 4')

src = ncryptpy.encoder_affine(src, 3, 4)
print('.'*80)
print(src)

src = ncryptpy.decoder_affine(src, 3, 4)
print('.'*80)
print(src)

usrc = src.decode('utf-8')
print('.'*80)
print(usrc)



# affine
print('-'*80)
print('affine 122 67')

src = ncryptpy.encoder_affine(src, 122, 67)
print('.'*80)
print(src)

src = ncryptpy.decoder_affine(src, 122, 67)
print('.'*80)
print(src)

usrc = src.decode('utf-8')
print('.'*80)
print(usrc)

