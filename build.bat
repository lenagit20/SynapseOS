@Echo off
echo Building SynapseOS

::
SET ARCH=arch/x86

SET AS=i686-elf-as
SET CC=i686-elf-gcc
SET LD=i686-elf-ld

SET CCFLAGS=-g -I include -ffreestanding -Wall -Wextra
SET LDFLAGS=%CCFLAGS% -nostdlib -lgcc

set OBJECTS=bin/kernel.o bin/%ARCH%/starter.o bin/io/tty.o bin/%ARCH%/memory/gdt.o bin/%ARCH%/memory/idt.o bin/%ARCH%/io/ports.o bin/%ARCH%/io/CMOS.o bin/libc/string.o bin/libc/stdlib.o  

:: 
RMDIR "bin" /S /Q
mkdir bin
cd bin
mkdir io
mkdir libc
mkdir arch
cd ARCH
mkdir x86
cd x86
mkdir io
mkdir memory
cd ..
cd ..
cd ..


::
echo Compiling Kernel
echo Using %CCFLAGS%
%CC% %CCFLAGS% -c kernel/kernel.c -o bin/kernel.o

echo Compiling modules
%CC% %CCFLAGS% -c modules/io/tty.c -o bin/io/tty.o

echo Compiling kernel libc
%CC% %CCFLAGS% -c libc/string.c -o bin/libc/string.o
%CC% %CCFLAGS% -c libc/stdlib.c -o bin/libc/stdlib.o

echo Compiling %ARCH% modules
%CC% %CCFLAGS% -c -Z %ARCH%/starter.s -o bin/%ARCH%/starter.o
%CC% %CCFLAGS% -c %ARCH%/io/ports.c -o bin/%ARCH%/io/ports.o
%CC% %CCFLAGS% -c %ARCH%/memory/gdt.c -o bin/%ARCH%/memory/gdt.o
%CC% %CCFLAGS% -c %ARCH%/memory/idt.c -o bin/%ARCH%/memory/idt.o
%CC% %CCFLAGS% -c %ARCH%/io/CMOS.c -o bin/%ARCH%/io/CMOS.o
%CC% %LDFLAGS% -T %ARCH%/link.ld -o bin/kernel.elf %OBJECTS%


pause