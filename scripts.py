#!/usr/bin/python3

import os
import shutil
import sys


def assert_run(cmd):
    code = os.system(cmd)
    if code != 0:
        exit(code)


def bind_compile(source, object):
    assert_run(
        f"i686-elf-gcc "
        f"-g -I include -ffreestanding -Wall -Wextra "
        f"-c {source} "
        f"-o {object}"
    )
    print(f"{source} -> {object}")


def bind_link(objects, executable):
    assert_run(
        f"i686-elf-gcc "
        f"-g -I include -ffreestanding -Wall -Wextra -nostdlib -lgcc "
        f"-T arch/x86/link.ld "
        f"-o {executable} "
        f"{' '.join(objects)}"
    )
    print("|", "\n| ".join(objects), f"\n-> {executable}")


def is_source(file):
    return file.split(".")[-1] in "cs"


def cmd_build():
    if os.path.exists("bin"):
        shutil.rmtree("bin")
    objects = []
    for (src, dst) in MAPPINGS.items():
        files = [i for i in os.listdir(src) if is_source(i)]
        os.makedirs(dst, exist_ok=True)
        for file in files:
            objects.append(os.path.join(dst, file[:-1] + "o"))
            bind_compile(
                os.path.join(src, file),
                objects[-1],
            )
    bind_link(objects, ELF)


def cmd_run():
    os.system(
        f"qemu-system-i386 "
        f"-d int -m 5 -boot d "
        f"-kernel {ELF} "
        f"-serial file:Qemu_log.log -no-reboot"
    )


ARCH = "arch/x86"
ELF = "bin/kernel.elf"
MAPPINGS = {
    "kernel": "bin",
    "modules/io": "bin/io",
    "modules": "bin",
    "libc": "bin/libc",
    f"{ARCH}": f"bin/{ARCH}",
    f"{ARCH}/io": f"bin/{ARCH}/io",
}

if "--silent" in sys.argv:
    print = lambda *_, **__: ...

if "all" in sys.argv:
    cmd_build()
    cmd_run()
else:
    if "build" in sys.argv:
        cmd_build()
    if "assert_run" in sys.argv:
        cmd_run()
