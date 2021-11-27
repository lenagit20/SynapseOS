@Echo off
echo Building SynapseOS

::
SET AS=i686-elf-as
SET CC=i686-elf-gcc
SET LD=i686-elf-ld

SET CCFLAGS=-g -I include -ffreestanding -Wall -Wextra
SET LDFLAGS=%CCFLAGS% -nostdlib -lgcc

set OBJECTS=bin/kernel.o bin/starter.o bin/io/tty.o bin/libc/string.o
SET ARCH=arch/x86

:: 
RMDIR "bin" /S /Q
mkdir bin
cd bin
mkdir io
mkdir libc
cd ..

::
echo Using %CCFLAGS%
%CC% %CCFLAGS% -c kernel/kernel.c -o bin/kernel.o
%CC% %CCFLAGS% -c modules/io/tty.c -o bin/io/tty.o
%CC% %CCFLAGS% -c libc/string.c -o bin/libc/string.o
%CC% %CCFLAGS% -c %ARCH%/starter.s -o bin/starter.o
%CC% %LDFLAGS% -T %ARCH%/link.ld -o bin/kernel.elf %OBJECTS%


pause