RESDIR = result
SRCDIR = src
AS = ../../../elftools/minias/minias
AR = ../../../elftools/ar/ar
LD = ../../../elftools/neatld/nld
CC = ../../../cproc/cproc

LSRC = $(SRCDIR)/loader.s $(SRCDIR)/sdmm.s $(SRCDIR)/ff.s
LOBJ = $(RESDIR)/loader.o $(RESDIR)/sdmm.o $(RESDIR)/ff.o

SRC = $(SRCDIR)/start.s $(SRCDIR)/xprintf.s
OBJ = $(RESDIR)/start.o $(RESDIR)/xprintf.o

LIB =  $(RESDIR)/sd.a 
BIN = $(RESDIR)/firmware.bin

.PHONY:		all

.PRECIOUS: $(RESDIR)/%.s

all: $(RESDIR) $(LIB) $(BIN)

$(RESDIR):
	mkdir -p $@

$(RESDIR)/%.s:$(SRCDIR)/%.c
	$(CC) -S -o $@ $<
	
$(RESDIR)/%.o:$(RESDIR)/%.s
	$(AS) -o $@ $< 

$(LIB):$(LOBJ)
	$(AR) -rcs $@ $^

$(RESDIR)/start.o:$(SRCDIR)/start.s
	$(AS) -o $@ $< 	

$(BIN):$(OBJ) $(LIB)
	$(LD) -t map.txt -s -e -p -mc=0 -o $@ $(OBJ) $(LIB)
	$(LD) -t map2.txt -p -mc=0 -o firm.elf $(OBJ) $(LIB)
	python3 mkhex.py $(RESDIR)/firmware
	 
clean:
	rm -f -r $(RESDIR)
