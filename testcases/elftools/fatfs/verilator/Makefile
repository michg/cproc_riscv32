

all: Vsystem

obj_dir/Vsystem.mk:
	verilator  -cc  --trace --exe -CFLAGS -fpermissive sd.c spi_sdcard.c tb.cpp picorv32.v system.v simsd.v --Wno-lint --Wno-unoptflat --Wno-combdly --Wno-redefmacro --top-module system


clean:
	rm -rf obj_dir
	rm -f Vsystem


Vsystem: obj_dir/Vsystem.mk
	make -C obj_dir -f Vsystem.mk
	cp obj_dir/Vsystem ../result
