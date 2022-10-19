RESDIR = ../bin/
CC = ../../cproc/cproc
AS = ../../elftools/minias/minias
AR = ../../elftools/ar/ar
C_FILES := $(wildcard *.c)
O_FILES := $(patsubst %.c,%.o,$(C_FILES))
OBJS = $(addprefix $(RESDIR), $(O_FILES)) 
LIBRARY := $(RESDIR)libminlibc.a
CFLAGS = -S -msf -nostdinc -I include
 
all: $(LIBRARY)


clean:
	$(RM) -f $(OBJ)

$(LIBRARY): $(OBJS)
	$(AR) -rcs $(LIBRARY) $(OBJS)
	rm -f $(OBJS) 

$(RESDIR)%.s:%.c
	$(CC) -o $@ $(CFLAGS) $<

$(RESDIR)%.o:$(RESDIR)%.s
	$(AS) -o $@ $< 
