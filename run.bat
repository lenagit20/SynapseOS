@echo qemu-system-i386 -d int -m 5 -boot d -kernel bin/kernel.elf -serial file:Qemu_log.log -no-reboot


@qemu-system-i386 -d int -m 5 -boot d -kernel bin/kernel.elf -serial file:Qemu_log.log -no-reboot

@pause