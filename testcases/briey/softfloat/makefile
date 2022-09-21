#
# Makefile for Libs
RESDIR = ../result/
CC=../../../cproc/cproc
AS=../../../elftools/minias/minias
LD=../../../elftools/neatld/nld
AR =../../../elftools/ar/ar
CFLAGS = -S -msf -I ../include


CSRCS = $(wildcard *.c)
ASRCS = $(patsubst %.c,%.s,$(CSRCS))
OSRCS = $(patsubst %.c,%.o,$(CSRCS))
OBJS = $(addprefix $(RESDIR), $(OSRCS))  
BIN = $(RESDIR)libfloat.a

.PHONY:		all

.PRECIOUS: $(RESDIR)%.s

all:		$(BIN)

$(RESDIR)%.s:%.c
	$(CC) -o $@ $(CFLAGS) $<

$(RESDIR)%.o:$(RESDIR)%.s
	$(AS) -o $@ $<

$(BIN):$(OBJS)
	$(AR) -rcs $@ $^
	rm -f $(OBJS)


