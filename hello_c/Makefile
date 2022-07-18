CLANG=${HOME}/opt/bin/mos-c64-clang++
XEMU=${HOME}/github/xemu/build/bin/xmega65.native

all: main 

music: Beyond_the_Zero.sid
	cat Beyond_the_Zero.sid | hexdump -v -e '"BYTE(0x" 1/1 "%02X" ")\n"' > music.ld

main: main.cpp
	${CLANG} main.cpp -Os -Wpedantic -o main_cpp.prg
	${CLANG} main.cpp -Os -o main.s -Wl,--lto-emit-asm

run: main
	${XEMU} -prg main.prg

format:
	clang-format -i main.cpp --style=WebKit

clean:
	rm -fR main.prg main.prg.elf music.ld *~ main.s
