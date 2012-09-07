SHELL   = /usr/bin/env sh
CC      = gcc
CFLAGS = -std=c99
LD      = gcc

bank_vault : bank_vault.c libsecurity.a
	$(CC) $(CLFAGS) $< -I. -L. -lsecurity -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

libsecurity.a : encrypt.o checksum.o
	ar -rcs libsecurity.a $^
