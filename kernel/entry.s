# taken from the xv6-riscv kernel
.section .text
.global _start
_start:
    # set up a stack for the BF language
    # stack is a stack with 4096 bytes
    la      sp, stack
    # jump to kernel in kmain.b
    call    kmain
spin:
    j       spin
