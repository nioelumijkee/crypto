#!/usr/bin/env python3
# test crypt.so

import crypt

# ---------------------------------------------------------------------------- #
print('#'*80)
src = b'abcdefg 0123456' # bytes
print(src)

src = crypt.encoder_caesar(src, 180)
print('-'*20)
print(src)

src = crypt.decoder_caesar(src, 180)
print('-'*20)
print(src)

# ---------------------------------------------------------------------------- #
print('#'*80)
src = 'abcdefg АБВГДЕИ 0123456' # utf-8
print(src)
src = src.encode('utf-8')

src = crypt.encoder_caesar(src, 180)
print('-'*20)
print(src)

src = crypt.decoder_caesar(src, 180)
print('-'*20)
print(src.decode('utf-8'))

