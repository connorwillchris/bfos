# taken from the xv6-riscv kernel
.section .text
.global _start
_start:
    # set up a stack for the BF language
    # stack is a stack with 4096 bytes
    la      sp, stack
    li      a0, 1024*4      # 4 KiB
    csrr    a1, mhartid     # get hartid
    addi    a1, a1, 1       # add 1 to hartid
    mul     a0, a0, a1      # a0 = 4 KiB * (hartid + 1)
    add     sp, sp, a0      # sp += a0
    # jump to kernel in kmain.b
    call    kmain
spin:
    j       spin
