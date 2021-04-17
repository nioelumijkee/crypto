# ---------------------------------------------------------------------------- #
CC = gcc
PYLIB = /usr/bin
PYINC = /usr/include/python3.7m
CFLAGS = -Wall -W -fPIC
CFLAGSPY += -I"$(PYINC)" -L"$(PYLIB)"
LIBS =
LIBSPY = -lpython3.7m

# ---------------------------------------------------------------------------- #
c: test.c crypt.c
	$(CC) $(CFLAGS) $(LIBS) -o test test.c

py: py.c crypt.c
	$(CC) -shared $(CFLAGS) $(CFLAGSPY) $(LIBSPY) -o crypt.so py.c

clean:
	rm -f *.so
	rm -f test
