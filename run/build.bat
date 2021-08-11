@Echo off
set VERSION="0008"

echo build SynapseOS %VERSION%
cd ..
echo *************************


REM Creating a Newline variable (the two blank lines are required!)
set NLM=^


set NL=^^^%NLM%%NLM%^%NLM%%NLM%
call :GetUnixTime UNIX_TIME

:vars
echo #define VERSION %VERSION% %NL%#define BUILD_UID "%UNIX_TIME%">src/include/kernel.h
SET AS=i686-elf-as
SET CC=i686-elf-gcc
SET LD=i686-elf-ld
SET SRC=./src
SET CCFLAGS=-std=gnu99 -ffreestanding -Wall -Wextra
SET LDFLAGS=-ffreestanding -nostdlib -lgcc

set OBJECTS=bin/kasm.o bin/kc.o bin/gdt.o bin/cmos.o bin/shell.o bin/interdesctbl.o bin/kbd.o bin/tty.o bin/ports.o bin/qemu_log.o bin/cpu_detect.o bin/memory_manager.o bin/stdlib.o


IF EXIST "./bin/" (
    echo Cleaning bin folder
    
) ELSE (
    mkdir bin & mkdir isodir & cd isodir & mkdir boot & cd boot & mkdir grub & cd ../../
)



echo Build asm kernel
fasm %SRC%/kernel.asm bin/kasm.o



echo Build kernel

%CC% %CCFLAGS% -c %SRC%/kernel.c -o ./bin/kc.o

%CC% %CCFLAGS% -c %SRC%/modules/stdlib.c -o ./bin/stdlib.o

%CC% %CCFLAGS% -c %SRC%/modules/memory_manager.c -o ./bin/memory_manager.o

%CC% %CCFLAGS% -c %SRC%/modules/gdt.c -o bin/gdt.o

%CC% %CCFLAGS% -c %SRC%/modules/cmos.c -o bin/cmos.o

::%CC% %CCFLAGS% -c %SRC%/modules/string.c -o bin/string.o

%CC% %CCFLAGS% -c %SRC%/modules/shell.c -o bin/shell.o

%CC% %CCFLAGS% -c %SRC%/modules/interdesctbl.c -o bin/interdesctbl.o

%CC% %CCFLAGS% -c %SRC%/modules/kbd.c -o bin/kbd.o

%CC% %CCFLAGS% -c %SRC%/modules/tty.c -o bin/tty.o

%CC% %CCFLAGS% -c %SRC%/modules/ports.c -o bin/ports.o

%CC% %CCFLAGS% -c %SRC%/modules/cpu_detect.c -o bin/cpu_detect.o

%CC% %CCFLAGS% -c %SRC%/modules/qemu_log.c -o bin/qemu_log.o

%CC% %LDFLAGS% -T %SRC%/link.ld -o bin/kernel.elf %OBJECTS%




echo Create iso

cp bin/kernel.elf isodir/boot/kernel.elf

cp %SRC%/grub.cfg isodir/boot/grub/grub.cfg

ubuntu run grub-mkrescue -o SynapseOS.iso isodir/



:GetUnixTime
setlocal enableextensions
for /f %%x in ('wmic path win32_utctime get /format:list ^| findstr "="') do (
    set %%x)
set /a z=(14-100%Month%%%100)/12, y=10000%Year%%%10000-z
set /a ut=y*365+y/4-y/100+y/400+(153*(100%Month%%%100+12*z-3)+2)/5+Day-719469
set /a ut=ut*86400+100%Hour%%%100*3600+100%Minute%%%100*60+100%Second%%%100
endlocal & set "%1=%ut%" & goto :vars

echo Done
pause