# Build and run script for linux

CC=i686-elf-gcc

BUILDFLAGS="-std=gnu11 -ffreestanding -Wall -Wextra -g"
LINKFLAGS="-ffreestanding -nostdlib -lgcc"

SRC="src"
OBJS="bin/*.o"

mkdir -p bin
mkdir -p isodir/boot/grub

# build code into objects
fasm $SRC/kernel.asm bin/kasm.o
fasm $SRC/modules/irq_wrappers.asm bin/irq_wrappers.o
$CC $BUILDFLAGS -c $SRC/kernel.c -o bin/kc.o
$CC $BUILDFLAGS -c $SRC/modules/stdlib.c -o bin/stdlib.o
$CC $BUILDFLAGS -c $SRC/modules/time.c -o bin/time.o
$CC $BUILDFLAGS -c $SRC/modules/phys_mem.c -o bin/phys_mem.o
$CC $BUILDFLAGS -c $SRC/modules/virt_mem.c -o bin/virt_mem.o
$CC $BUILDFLAGS -c $SRC/modules/kheap.c -o bin/kheap.o
$CC $BUILDFLAGS -c $SRC/modules/cpu_detect.c -o bin/cpu_detect.o
$CC $BUILDFLAGS -c $SRC/modules/gdt.c -o bin/gdt.o
$CC $BUILDFLAGS -c $SRC/modules/idt.c -o bin/idt.o
$CC $BUILDFLAGS -c $SRC/modules/pic.c -o bin/pic.o
$CC $BUILDFLAGS -c $SRC/modules/kbd.c -o bin/kbd.o
$CC $BUILDFLAGS -c $SRC/modules/ports.c -o bin/ports.o
$CC $BUILDFLAGS -c $SRC/modules/qemu_log.c -o bin/qemu_log.o
$CC $BUILDFLAGS -c $SRC/modules/shell.c -o bin/shell.o
$CC $BUILDFLAGS -c $SRC/modules/NeraMath.c -o bin/NeraMath.o
$CC $BUILDFLAGS -c $SRC/modules/tty.c -o bin/tty.o

# link objects
$CC $LINKFLAGS -T $SRC/link.ld -o isodir/boot/kernel.elf $OBJS

cp $SRC/grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o SynapseOS.iso isodir/
