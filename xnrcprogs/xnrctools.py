#!/usr/bin/env python3
"""xnrctools.py: Utility for compiling and run xnrcprog programs."""
from collections import namedtuple
import shutil
import subprocess
import os
from typing import List, Dict


XNRSRCDIR = os.path.join(os.path.dirname(__file__), "src")
XNRLIBDIR = os.path.join(os.path.dirname(__file__), "lib")
XNRBINDIR = os.path.join(os.path.dirname(__file__), "bin")
XNRBUILDIR = os.path.join(os.path.dirname(__file__), "build")

XNRCFLAG = "-c -g -O2".split()
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
    # print(f" -- C compiler: {_cc}")
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
        self._src: Dict[str, List[str]] = arg.src
        self._bin: str = arg.bin
        self._lib: List[str] = arg.lib
        self._cflags: List[str] = arg.cflags
        self._clibs: List[str] = arg.clibs

    def _make_executable(self, cc, ofiles: List[str]):
        """make executable"""
        cmd = [cc, "-o", self._name]
        cmd.extend(ofiles)
        _ = subprocess.run(cmd)

    def compile_src(self) -> None:
        """Compiler source"""
        here = os.getcwd()
        print(f"directory: {here}")
        
        sources = self._src
        data = {}
        for file, headers in sources.items():
            if os.path.isfile(file):
                key = os.path.basename(file)
                print(f"Found source file: {file} with basename:: {key}")
                shutil.copy(file, XNRBUILDIR)
                data[os.path.basename(file)] = list()
                for header in headers:
                    if os.path.isfile(header):
                        hdr = os.path.basename(header)
                        print(f"\tHeader file: {header} with basename:: {hdr}")
                        shutil.copy(header, XNRBUILDIR)
                        data[key].append(hdr)
        # copy src files to build-dir
        # copy header files to build-dir
        print(f"{data!r}")
        os.chdir(XNRBUILDIR)
        cc = xnr_get_compiler()
        print(f" -- C compiler: {cc}")
        cmd = [cc]
        cmd.extend(XNRCFLAG)
        for key in data:
            _extra = [key]
            for h in data[key]:
                _extra.append(h)
            cmd.extend(_extra)
            txt = " ".join(cmd)
            print(f"Running command:\n  {txt}")
            subprocess.run(cmd)

        ofiles = [f"{os.path.splitext(file)[0]}.o" for file in data]
        print(ofiles)
        self._make_executable(cc, ofiles)

        os.chdir(here)

        

    def _build_bin(self, arg):
        pass



def main():
    #_ = xnr_get_compiler()
    xnrgrepdata = XNRData(
        name="xnrgrep",
        src={
            "src/xnroptions.c": ["src/xnroptions.h"],
            "src/xnrgrep.c": ["src/xnroptions.h"]
        },
        bin="xnrgrep",
        lib=None,
        cflags=None,
        clibs=None,
    )
    xnrgrep = XNRCTools(xnrgrepdata)
    xnrgrep.compile_src()


if __name__ == "__main__":
    main()
