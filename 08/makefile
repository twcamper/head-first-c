SHELL   = /usr/bin/env sh
CC      = gcc
CFLAGS = -std=c99
LD      = gcc
AR      = ar

all : bank_vault elliptical

# REMEMBER! $ export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/08
elliptical : elliptical.c libcalories.so
	$(CC) $(CLFAGS) $< -I. -L. -lcalories -o $@

bank_vault : bank_vault.c libsecurity.a
	$(CC) $(CLFAGS) $< -I. -L. -lsecurity -o $@

%.o : %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

calories.o : calories.c
	$(CC) $(CFLAGS) -I. -fPIC -c $< -o $@

libcalories.so : calories.o
	$(CC) -shared $< -o $@

libsecurity.a : encrypt.o checksum.o
	$(AR) -rcs libsecurity.a $^
