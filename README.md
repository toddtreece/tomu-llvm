# Tomu Clang/LLVM Hello World

This is a simple LED toggle example for [Tomu][tomu] using Clang
instead of the GNU Arm Embedded Toolchain. This example does not
use any external libraries, but it does borrow some macros from
[libopencm3][cm3].

## Setup

macOS:
```
$ brew install --with-toolchain llvm
$ brew install dfu-util
$ echo 'export PATH="/usr/local/opt/llvm/bin:$PATH"' >> ~/.bash_profile
```

## Usage

Build:
```
$ make
```

Clean:
```
$ make clean
```

Build & Flash:
```
$ make flash
```

## License

This example code is released under the terms of the GNU Lesser General
Public License (LGPL), version 3 or later.

See [LICENSE][license] for details.

[tomu]: https://tomu.im/
[cm3]: https://github.com/libopencm3/libopencm3
[license]: LICENSE
