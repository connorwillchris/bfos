AS = riscv64-unknown-elf-as
LD = riscv64-unknown-elf-ld

all:

kernel: all

qemu: all
	qemu-system-riscv64 -nographic -machine virt -m 128M -kernel kernel
