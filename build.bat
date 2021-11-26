@Echo off
echo Building SynapseOS

::
SET AS=i686-elf-as
SET CC=i686-elf-gcc
SET LD=i686-elf-ld

SET CCFLAGS=-g -I include -ffreestanding -Wall -Wextra -O2
SET LDFLAGS=%CCFLAGS% -nostdlib -lgcc

:: 
RMDIR "bin" /S /Q
mkdir bin
cd bin
mkdir io
cd ..

::
echo Using %CCFLAGS%
%CC% %CCFLAGS% -c kernel/kernel.c -o bin/kernel.o
%CC% %CCFLAGS% -c io/tty.c -o bin/io/tty.o
%CC% %CCFLAGS% -c x86/starter.s -o bin/starter.o
%CC% %LDFLAGS% -T x86/link.ld -o bin/kernel.elf bin/kernel.o bin/starter.o bin/io/tty.o


pause