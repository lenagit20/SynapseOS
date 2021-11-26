@Echo off
echo Building SynapseOS

::
SET AS=i686-elf-as
SET CC=i686-elf-gcc
SET LD=i686-elf-ld

SET CCFLAGS=-I include -ffreestanding -Wall -Wextra
SET LDFLAGS=%CCFLAGS% -nostdlib -lgcc

:: 
RMDIR "bin" /S /Q
mkdir bin

::
echo Using %CCFLAGS%
%CC% %CCFLAGS% -c kernel/kernel.c -o bin/kernel.o
%CC% %CCFLAGS% -c x86/starter.s -o bin/starter.o
%CC% %LDFLAGS% -T x86/link.ld -o bin/kernel.elf bin/kernel.o bin/starter.o


pause