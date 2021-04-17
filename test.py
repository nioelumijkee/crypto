#!/usr/bin/env python3
# test crypt.so

import crypt

print('-'*80)
src = b'abcdefg'
print(src)
print(type(src))
src = crypt.encoder_caesar(src, 180)
print(src)
src = crypt.decoder_caesar(src, 180)
print(src)


print('-'*80)
src = 'Абвгде'.encode('utf-8')
print(src)
print(type(src))
src = crypt.encoder_caesar(src, 180)
print(src)
src = crypt.decoder_caesar(src, 180)
print(src)


print('-'*80)
src = 'asca'.encode('utf-8')
print(src)
print(type(src))
src = crypt.encoder_caesar(src, 23)
print(src)
src = crypt.decoder_caesar(src, 23)
print(src)


print('-'*80)
src = 'Ниоэлумиджке и Лисенок...'.encode('utf-8')
print(src)
print(type(src))
src = crypt.encoder_caesar(src, 1)
print(src)
src = crypt.decoder_caesar(src, 1)
print(src)

