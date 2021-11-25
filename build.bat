@Echo off
echo Building SynapseOS

::
SET AS=x86_64-elf-as
SET CC=x86_64-elf-gcc
SET LD=x86_64-elf-ld

SET CCFLAGS= -O2 -g -ffreestanding -Wall -Wextra -mcmodel=large
SET LDFLAGS= -O2 -g -ffreestanding -Wall -Wextra -nostdlib -lgcc -mcmodel=large

:: Checking for the presence of a folder and, if not, creating one
IF EXIST "bin/" (
    echo Cleaning bin folder
    del bin/*
) ELSE (
    mkdir bin
)

echo Using %CCFLAGS%
%CC% %CCFLAGS% -c kernel/kernel.c -o bin/kernel.o
%CC% %CCFLAGS% -c x86_64/starter.s -o bin/starter.o
%CC% %LDFLAGS% -T x86_64/link.ld -o bin/kernel.elf bin/kernel.o bin/starter.o

pause