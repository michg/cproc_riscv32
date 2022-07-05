.globl main
.globl _start
_start:
lui x2, 0x1F
jal x1, main
ebreak
nop
.globl rdcyc
.align	4
rdcyc:
rdcycle x10
jalr x0,x1,0
