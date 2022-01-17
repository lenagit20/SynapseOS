import abc
import os
import shutil
import subprocess
import sys


class Toolset:
    def compile(self, source: str, object: str) -> None:
        self._run(
            f"i686-elf-gcc "
            f"-g -I include -ffreestanding -Wall -Wextra "
            f"-c {source} "
            f"-o {object}"
        )
        print(f"{source} -> {object}")

    def link(self, objects: list[str], executable: str) -> None:
        self._run(
            f"i686-elf-gcc "
            f"-g -I include -ffreestanding -Wall -Wextra -nostdlib -lgcc "
            f"-T arch/x86/link.ld "
            f"-o {executable} "
            f"{' '.join(objects)}"
        )
        print("|", "\n| ".join(objects), f"\n-> {executable}")

    def is_source(self, file: str) -> bool:
        return file.split(".")[-1] in "cs"

    def _run(self, cmd: str) -> None:
        code = os.system(cmd)
        if code != 0:
            exit(code)


def _build(toolset: Toolset):
    objects = []
    for (src, dst) in MAPPINGS.items():
        files = [i for i in os.listdir(src) if toolset.is_source(i)]
        os.makedirs(dst, exist_ok=True)
        for file in files:
            objects.append(os.path.join(dst, file[:-1] + "o"))
            toolset.compile(
                os.path.join(src, file),
                objects[-1],
            )
    toolset.link(objects, ELF)


def build():
    shutil.rmtree("bin")
    _build(Toolset())


def run():
    os.system(
        f"qemu-system-i386 "
        f"-d int -m 5 -boot d "
        f"-kernel {ELF}"
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
    build()
    run()
else:
    if "build" in sys.argv:
        build()
    if "run" in sys.argv:
        run()
