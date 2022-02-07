GRUB_CONFIG='''
menuentry "SynapseOS" {
    multiboot /boot/kernel.elf   
    boot
    }
'''


rm -rf isodir
mkdir -p isodir/boot/grub

cp bin/kernel.elf isodir/boot/kernel.elf
echo $GRUB_CONFIG> isodir/boot/grub/grub.cfg

grub-mkrescue -o SynapseOS.iso isodir/