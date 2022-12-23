.globl main
.globl _start
_start:
lui x2, 0x1F
bss_init:
la x10, bss_start
la x11, bss_fin
bss_loop:
beq x10,x11,bss_done
sw x0,0(x10)
addi x10,x10,4
j bss_loop
bss_done: 
jal x1, main
ebreak
nop
.globl rdcyc
.align	4
rdcyc:
rdcycle x10
jalr x0,x1,0
