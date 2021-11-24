echo Building SynapseOS

::
SET AS=x86_64-elf-as
SET CC=x86_64-elf-gcc
SET LD=x86_64-elf-ld

SET CCFLAGS= -O0 -g -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -wall -Wextra -masm=intel
SET LDFLAGS= -O0 -g -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -wall -Wextra -nostdlib -lgcc -masm=intel

:: Checking for the presence of a folder and, if not, creating one
IF EXIST "./bin/" (
    echo Cleaning bin folder
    del ./bin/*
) ELSE (
    mkdir bin & mkdir isodir & cd isodir & mkdir boot & cd boot & mkdir grub & cd ../../
)

echo Using %CCFLAGS%
%CC% %CCFLAGS% -c ./kernel/kernel.c -o ./bin/kc.o


