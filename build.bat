@Echo off
echo Building SynapseOS

::
SET ARCH=arch/x86

SET AS=i686-elf-as
SET CC=i686-elf-gcc
SET LD=i686-elf-ld

SET CCFLAGS=-g -I include -ffreestanding -Wall -Wextra 
SET LDFLAGS=%CCFLAGS% -nostdlib -lgcc

set MODULES_OBJ=bin/io/tty.o bin/exceptions.o bin/lang0x42.o bin/io/keyboard.o bin/shell.o 
set DRIVERS_OBJ=bin/drivers/floppy.o 
set LIBK_OBJ=bin/libk/string.o bin/libk/stdlib.o 
set ARCH_OBJ=bin/%ARCH%/gdt.o bin/%ARCH%/idt.o bin/%ARCH%/io/ports.o bin/%ARCH%/io/CMOS.o bin/%ARCH%/starter.o 
set OBJECTS=bin/kernel.o %MODULES_OBJ% %LIBK_OBJ% %ARCH_OBJ% %DRIVERS_OBJ% 

:: 
RMDIR "bin" /S /Q
mkdir bin
cd bin
mkdir io
mkdir libk
mkdir arch
mkdir drivers
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
%CC% %CCFLAGS% -c modules/io/keyboard.c -o bin/io/keyboard.o
%CC% %CCFLAGS% -c modules/exceptions.c -o bin/exceptions.o
%CC% %CCFLAGS% -c modules/lang0x42.c -o bin/lang0x42.o
%CC% %CCFLAGS% -c modules/shell.c -o bin/shell.o

echo Compiling kernel libk
%CC% %CCFLAGS% -c libk/string.c -o bin/libk/string.o
%CC% %CCFLAGS% -c libk/stdlib.c -o bin/libk/stdlib.o

echo Compiling drivers
%CC% %CCFLAGS% -c drivers/floppy.c -o bin/drivers/floppy.o

echo Compiling %ARCH% modules
%CC% %CCFLAGS% -c %ARCH%/starter.s -o bin/%ARCH%/starter.o
%CC% %CCFLAGS% -c %ARCH%/io/ports.c -o bin/%ARCH%/io/ports.o
%CC% %CCFLAGS% -c %ARCH%/io/CMOS.c -o bin/%ARCH%/io/CMOS.o
%CC% %CCFLAGS% -c %ARCH%/gdt.c -o bin/%ARCH%/gdt.o
%CC% %CCFLAGS% -c %ARCH%/idt.c -o bin/%ARCH%/idt.o


echo Linking...
%CC% %LDFLAGS% -T %ARCH%/link.ld -o bin/kernel.elf %OBJECTS%


TIMEOUT /T 5 