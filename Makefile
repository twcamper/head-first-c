# tested with GNU make 3.81
SHELL   = /usr/bin/env sh
CC      = gcc
CFLAGS = -std=c99
LD      = gcc

#### targets and prerequisites ####
SRCS        = $(shell find . -name '*.c' | tr '\n' ' ')
OBJECTS     = $(filter-out %encrypt.o %totaller.o, $(SRCS:.c=.o))
EXECUTABLES = $(filter-out %message_hider %encrypt, $(SRCS:.c=))

#### One target per *.asm source file found above ####
all: $(EXECUTABLES) 04/message_hider

04/message_hider: 04/message_hider.o 04/encrypt.o
	$(LD) $^ -o $@

#### Build all executable targets, using a 'Static Pattern Rule' (GNU make manual, 4.11) ####
$(EXECUTABLES) : % : %.o
	$(LD) $< -o $@

#### compiled object files ####
$(OBJECTS) : %.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

04/encrypt.o : 04/encrypt.c 04/encrypt.h
	$(CC) -c $(CFLAGS) $< -o $@

04/totaller.o : 04/totaller.c 04/totaller.h
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY : .gitignore clean clean-obj clean-bin
.gitignore:
	@~/scripts/add-executables-to-gitignore.sh

clean: clean-obj clean-bin

# GNU xargs
XARGS_RM = xargs --no-run-if-empty rm -fv

clean-obj:
	@find . -name '*.o' | $(XARGS_RM)

clean-bin:
	@find . -perm +111 -type f | grep -v \.git | $(XARGS_RM)
