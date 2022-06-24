CLANG=${HOME}/llvm-mos/bin/mos-mega65-clang
XEMU=${HOME}/github/xemu/build/bin/xmega65.native

all: main 

main: main.c
	${CLANG} main.c -Os -o main.prg

run: main
	${XEMU} -prg main.prg

clean:
	rm -fR main.prg main.prg.elf
