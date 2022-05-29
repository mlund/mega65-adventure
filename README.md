# MEGA65 Programming Playground

This is a playground for testing programming on the MEGAi 65 8-bit computer.

## Rust using llvm-mos

The `hello_rust` directory contains a simple project that compiles 6502 using
[llvm-mos](https://llvm-mos.org) from wrapped Rust code. It requires a working
Rust installation and the [llvm-mos-sdk](https://github.com/llvm-mos/llvm-mos-sdk#getting-started).
Compile and run with:

~~~
    cd hello_rust
    make
    xmega65.native -prg main.prg -prgmode 64
~~~

### Things to to:

- [x] Added convenience `peek` and `poke` Rust macros
- [x] Begin mega64 module with hardware registers (see e.g. KickC headers)
- [ ] Inline assembler?
- [ ] Start programme in MEGA65 mode

### Usefil links

- http://forum.6502.org/viewtopic.php?p=84048#p84048
- https://gergo.erdi.hu/blog/2021-09-18-rust_on_the_mos_6502__beyond_fibonacci/

