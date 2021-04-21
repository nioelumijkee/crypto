# ---------------------------------------------------------------------------- #
CC = gcc
PYLIB = /usr/bin
PYINC = /usr/include/python3.7m
CFLAGS = -Wall -W -fPIC
CFLAGSPY += -I"$(PYINC)" -L"$(PYLIB)"
LIBS =
LIBSPY = -lpython3.7m

CSRCDIR = ./src
PYSRCDIR = ./py



# ---------------------------------------------------------------------------- #
all: py

py: $(CSRCDIR)/py.c  $(CSRCDIR)/crypt.c  $(CSRCDIR)/hash.c
	$(CC) -shared $(CFLAGS) $(CFLAGSPY) $(LIBSPY) -o ncryptpy.so $(CSRCDIR)/py.c

clean:
	rm -f *.so
