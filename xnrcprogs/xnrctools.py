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

XNRCFLAG = "-c -g -O2"
XNRCLIBS = None

XNRData = namedtuple("XNRData", "name src bin lib cflags clibs")


class XNRCTools:
    """XNRCTools"""

    def __init__(self, arg: XNRData) -> None:
        """Initialize XNRCTools"""
        self._name: str = arg.name
        self._src: List[str] = arg.src
        self._bin: str = arg.bin
        self._lib: List[str] = arg.lib
        self._cflags: List[str] = arg.cflags
        self._clibs: List[str] = arg.clibs

    def _get_compiler(self):
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
    xnrctool = XNRCTools(
        XNRData(name="", src=None, bin=None, lib=None,cflags=None, clibs=None)
    )
    xnrctool._get_compiler()


if __name__ == "__main__":
    main()
