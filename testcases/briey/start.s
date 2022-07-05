.globl main
.globl _start
_start:
csrwi 2, 1 
lui x2, 0x80030
jal x1, main
l1:
j l1
