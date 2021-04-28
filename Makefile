# ---------------------------------------------------------------------------- #
CC = gcc
PYLIB = /usr/bin
PYINC = /usr/include/python3.7m
CFLAGS = -Wall -W -fPIC
CFLAGSPY += -I"$(PYINC)" -L"$(PYLIB)"
LIBS =
LIBSPY = -lpython3.7m

CSRCDIR = ./src

SRC = \
$(CSRCDIR)/ncp.c \
$(CSRCDIR)/hash.c \
$(CSRCDIR)/random.c \
$(CSRCDIR)/add.c \
$(CSRCDIR)/crypt.c


# ---------------------------------------------------------------------------- #
all: ncp

ncp: $(SRC)
	$(CC) -shared $(CFLAGS) $(CFLAGSPY) $(LIBSPY) -o ncp.so $(CSRCDIR)/ncp.c

clean:
	rm -f *.so
