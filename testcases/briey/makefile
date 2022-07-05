RESDIR = result/
CC=../../cproc/cproc
AS=../../elftools/minias/minias
LD=../../elftools/neatld/nld
AR = ../../elftools/ar/ar
CFLAGS = -S -I include 

LIBS = $(RESDIR)/libmathhf.a

CSRCS = es.c
ASRCS = start.s 
OSRCS = start.o es.o
OBJS = $(addprefix $(RESDIR), $(OSRCS))
BIN = $(RESDIR)firmware.bin

.PHONY:		all

.PRECIOUS:$(RESDIR)%.s

all:$(RESDIR) $(LIBS) $(BIN)

$(LIBS):
	make -r -C libmathf
    

$(RESDIR):
	mkdir -p $@ 

$(RESDIR)%.s:%.c
	$(CC) $(CFLAGS) -o $@ $<

$(RESDIR)%.o:%.s
	$(AS) -o $@ $<

$(RESDIR)%.o:$(RESDIR)%.s
	$(AS) -o $@ $<

$(BIN):$(OBJS) $(LIBS)
	$(LD) -s -e -o $@ $^
	$(LD) -mc=0 -o $(RESDIR)firm.elf $^
	python3 mkhex.py $(RESDIR)firmware.bin
 

clean:
		rm -f -r $(RESDIR)
