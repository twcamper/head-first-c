PREFIX = ../

include $(PREFIX)make/env.mk
EXCLUDE = ./ikkp-server.c ./wp-client.c
include $(PREFIX)make/generic.mk

COMPILE = $(CC) -c $(CFLAGS) $<
LINK    = $(LD) $^ -o $@

all:  $(EXECUTABLES) \
	    ikkp-server \
			wp-client

wp-client: wp-client.o $(LIBS)/error.o
	$(LINK)

wp-client.o: %.o : %.c $(LIBS)/error.o
	$(COMPILE)

ikkp-server: ikkp-server.o $(LIBS)/error.o $(LIBS)/signals.o $(LIBS)/knock-knock-database.o
	$(LINK)

ikkp-server.o: %.o : %.c $(INCS)/error.h $(INCS)/signals.h $(INCS)/knock-knock-database.h
	$(COMPILE)

include $(PREFIX)make/clean.mk
