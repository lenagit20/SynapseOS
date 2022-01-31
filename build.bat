@Echo off
echo Building SynapseOS

::
SET ARCH=arch/x86

SET AS=i686-elf-as
SET CC=i686-elf-gcc
SET LD=i686-elf-ld

SET CCFLAGS=-g -I include -ffreestanding -Wall -Wextra -Og
SET LDFLAGS=%CCFLAGS% -nostdlib -lgcc

set MODULES_OBJ=bin/io/tty.o bin/exceptions.o bin/lang0x42.o
set LIBC_OBJ=bin/libc/string.o bin/libc/stdlib.o 
set ARCH_OBJ=bin/%ARCH%/gdt.o bin/%ARCH%/idt.o bin/%ARCH%/io/ports.o bin/%ARCH%/io/CMOS.o
set OBJECTS=bin/kernel.o bin/%ARCH%/starter.o %MODULES_OBJ% %LIBC_OBJ% %ARCH_OBJ%

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
cd ..
cd ..
cd ..


::
echo Compiling Kernel
echo Using %CCFLAGS%
%CC% %CCFLAGS% -c kernel/kernel.c -o bin/kernel.o

echo Compiling modules
%CC% %CCFLAGS% -c modules/io/tty.c -o bin/io/tty.o
%CC% %CCFLAGS% -c modules/exceptions.c -o bin/exceptions.o
%CC% %CCFLAGS% -c modules/lang0x42.c -o bin/lang0x42.o

echo Compiling kernel libc
%CC% %CCFLAGS% -c libc/string.c -o bin/libc/string.o
%CC% %CCFLAGS% -c libc/stdlib.c -o bin/libc/stdlib.o

echo Compiling %ARCH% modules
%CC% %CCFLAGS% -c %ARCH%/starter.s -o bin/%ARCH%/starter.o
%CC% %CCFLAGS% -c %ARCH%/io/ports.c -o bin/%ARCH%/io/ports.o
%CC% %CCFLAGS% -c %ARCH%/gdt.c -o bin/%ARCH%/gdt.o
%CC% %CCFLAGS% -c %ARCH%/idt.c -o bin/%ARCH%/idt.o
%CC% %CCFLAGS% -c %ARCH%/io/CMOS.c -o bin/%ARCH%/io/CMOS.o


%CC% %LDFLAGS% -T %ARCH%/link.ld -o bin/kernel.elf %OBJECTS%


pause