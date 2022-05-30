CLANG=${HOME}/llvm-mos/bin/mos-c64-clang

all: main 

# assemble main 6502 prg file
main: main.ll wrapper.c
	${CLANG} wrapper.c main.ll -o main.prg -Os

# optional assembler output (verbose; contains excess code that will be optimized out)
main.s: main.ll wrapper.c
	${CLANG} wrapper.c main.ll -o main.s -Wl,--lto-emit-asm

# translate rust code
main.ll: main.rs mega65.rs
	rustc main.rs --emit=llvm-ir --crate-type=rlib -C debuginfo=0 -C opt-level=1

clean:
	rm -fR main.prg main.prg.elf main.ll main.s
