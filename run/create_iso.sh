echo Create iso
cp bin/kernel.elf isodir/boot/kernel.elf
cp %SRC%/grub.cfg isodir/boot/grub/grub.cfg
grub-mkrescue -o SynapseOS.iso isodir/