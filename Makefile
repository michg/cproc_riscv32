#
# Makefile for building the compiler and elftools
#

.PHONY:		all clean

all:
		make -C cproc all
		make -C qbe_riscv32 install PREFIX=usr
		make -C elftools
		make -C libs
		
clean:
		make -C cproc clean
		make -C qbe_riscv32 clean
		make -C elftools clean
