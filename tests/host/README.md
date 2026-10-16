# Host regression tests

Run on a Linux host without an EtherCAT controller or slave:

```sh
cmake -S tests/host -B build/host -DCMAKE_BUILD_TYPE=Release
cmake --build build/host -j4
ctest --test-dir build/host --output-on-failure
```

The tests reproduce the shared `CC_H` guard used by OSAL, with both include
orders and repeated inclusion of `cc.h`. They verify SOES byte order flags,
wire-format bitfields, byte-order conversions, and the size and field offsets
of `_ESCvar` across translation units. Both executables link the real
`ESCvar` definition from `ecat_slv.c`. Unused hardware-dependent functions are
discarded by the linker; no hardware stubs are needed. One executable uses
LTO, with GCC type mismatches treated as errors, and one does not.

The small OSAL stand-in only models its shared compiler guard and packing
macros. These tests cover SOES's structure layout, not every OSAL compiler
macro or API.

To test a big-endian target with the PowerPC Linux cross compiler and QEMU:

```sh
cmake -S tests/host -B build/host-ppc -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_SYSTEM_NAME=Linux -DCMAKE_SYSTEM_PROCESSOR=powerpc \
  -DCMAKE_C_COMPILER=powerpc-linux-gnu-gcc \
  '-DCMAKE_CROSSCOMPILING_EMULATOR=qemu-ppc;-L;/usr/powerpc-linux-gnu'
cmake --build build/host-ppc -j4
ctest --test-dir build/host-ppc --output-on-failure
```
