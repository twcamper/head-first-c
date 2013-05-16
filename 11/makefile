PREFIX = ../

include $(PREFIX)make/env.mk
EXCLUDE = ./ikkp_server.c
include $(PREFIX)make/generic.mk

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

all:  $(EXECUTABLES) \
	    ikkp_server

ikkp_server: ikkp_server.o $(LIBS)/error.o $(LIBS)/signals.o
	$(LINK)

ikkp_server.o: %.o : %.c $(INCS)/error.h $(INCS)/signals.h
	$(COMPILE)

include $(PREFIX)make/clean.mk
