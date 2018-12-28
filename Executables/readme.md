Initially only Win32 files built from the C or C++ version with Mingw-32 (gcc8.x) or newer.
(usually 12-20KB if stripped but may be 40-60k otherwise)

The libstdc++-6.dll file may be needed for any C++ build EXE's. This is a requirement of MingW for C++ builds only. Since most or all the executables are from C builds, this file may not be needed at all. You will get a C++ Error If you need this file. Simply place it in the same directory as the problem EXE or include it in the PATH environment variable. If you build your own, you may already have this file or you won't need it at all.

In the few cases where only a Quick Basic version exists, QB64 rebuilt with Mingw-32 (gcc 8.x) or higher will be used.
(Usually files about 1Mb or larger)

If Linux gets included, then files will likely be built with the newest gcc build available.

Note that there is a Linux version of QB64 and there is also Wine. For some of the computationally or
file intensive programs you may want to use a native build from C or C++ source code.
