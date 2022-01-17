#!/usr/bin/python3

import abc
import os
import shutil
import subprocess
import sys


def run(cmd: str) -> None:
    code = os.system(cmd)
    if code != 0:
        exit(code)


def compile(source: str, object: str) -> None:
    run(
        f"i686-elf-gcc "
        f"-g -I include -ffreestanding -Wall -Wextra "
        f"-c {source} "
        f"-o {object}"
    )
    print(f"{source} -> {object}")


def link(objects: list[str], executable: str) -> None:
    run(
        f"i686-elf-gcc "
        f"-g -I include -ffreestanding -Wall -Wextra -nostdlib -lgcc "
        f"-T arch/x86/link.ld "
        f"-o {executable} "
        f"{' '.join(objects)}"
    )
    print("|", "\n| ".join(objects), f"\n-> {executable}")


def is_source(file: str) -> bool:
    return file.split(".")[-1] in "cs"


def build():
    objects = []
    for (src, dst) in MAPPINGS.items():
        files = [i for i in os.listdir(src) if is_source(i)]
        os.makedirs(dst, exist_ok=True)
        for file in files:
            objects.append(os.path.join(dst, file[:-1] + "o"))
            compile(
                os.path.join(src, file),
                objects[-1],
            )
    link(objects, ELF)


def cmd_build():
    if os.path.exists("bin"):
        shutil.rmtree("bin")
    build()


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
    if "run" in sys.argv:
        cmd_run()
