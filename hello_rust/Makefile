CLANG=${HOME}/llvm-mos/bin/clang --config ${HOME}/llvm-mos/bin/mos-c64.cfg -O1

all: main.xex main.s

main.xex: main.ll wrapper.c
	${CLANG} wrapper.c main.ll -o main.prg

main.s: main.ll wrapper.c
	${CLANG} wrapper.c main.ll -o main.s -Wl,--lto-emit-asm

main.ll: main.rs
	rustc main.rs --emit=llvm-ir --crate-type=rlib -C debuginfo=0 -C opt-level=1

clean:
	rm -fR main.prg main.prg.elf main.ll main.s
