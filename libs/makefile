RESDIR = bin/
CC=../cproc/cproc
AS=../elftools/minias/minias
LD=../elftools/neatld/nld
AR = ../elftools/ar/ar
CFLAGS = -S -I include

LIBS = $(RESDIR)/libmathhf.a $(RESDIR)/libmathsf.a $(RESDIR)/libsoftfloat.a $(RESDIR)/libminlibc.a


.PHONY:		all

.PRECIOUS:$(RESDIR)%.s

all:$(RESDIR) $(LIBS)

$(LIBS):
	make -r -C libmath -f makehf
	make -r -C libmath -f makesf
	make -r -C libsoftfloat
	make -r -C libminlibc

$(RESDIR):
	mkdir -p $@

clean:
	rm -f -r $(RESDIR)
