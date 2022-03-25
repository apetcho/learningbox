#!/usr/bin/env python3
"""xnrctools.py: Utility for compiling and run xnrcprog programs."""
from collections import namedtuple
import shutil
import subprocess
import os
from typing import List


XNRSRCDIR = os.path.join(os.path.dirname(__file__), "src")
XNRLIBDIR = os.path.join(os.path.dirname(__file__), "lib")
XNRBINDIR = os.path.join(os.path.dirname(__file__), "bin")
XNRBUILDIR = os.path.join(os.path.dirname(__file__), "build")

XNRCFLAG = "-c -g -O2"
XNRCLIBS = None

XNRData = namedtuple("XNRData", "name src bin lib cflags clibs")

def xnr_get_compiler() -> None:
    """Get compiler"""
    _cc = shutil.which("clang")
    if _cc is None:
        for cc in ("clang", "gcc"):
            _cc = shutil.which(cc)
            if _cc is not None:
                break

    if _cc is None:
        raise ValueError("No C compiler found on this system")
    print(f" -- C compiler: {_cc}")
    return _cc


class XNRCTools:
    """XNRCTools"""

    @staticmethod
    def process(arg):
        """Process"""
        here = os.getcwd()
        os.chdir(XNRBUILDIR)
        _ = subprocess.run(arg)
        os.chdir(here)

    def __init__(self, arg: XNRData) -> None:
        """Initialize XNRCTools"""
        self._name: str = arg.name
        self._src: List[str] = arg.src
        self._bin: str = arg.bin
        self._lib: List[str] = arg.lib
        self._cflags: List[str] = arg.cflags
        self._clibs: List[str] = arg.clibs

    def _compile_src(self, arg: List[str]) -> None:
        """Compiler source"""
        here = os.getcwd()
        os.chdir(XNRBUILDIR)
        _ = subprocess.run(arg)
        os.chdir(here)

    def _build_bin(self, arg):
        pass

    def _get_compiler(self) -> None:
        """Get compiler"""
        self._cc = shutil.which("clang")
        if self._cc is None:
            for cc in ("clang", "gcc"):
                self._cc = shutil.which(cc)
                if self._cc is not None:
                    break

        if self._cc is None:
            raise ValueError("No C compiler found on this system")
        print(f" -- C compiler: {self._cc}")


def main():
    _ = xnr_get_compiler()


if __name__ == "__main__":
    main()
