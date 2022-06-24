BSA=${HOME}/bin/bsa
XEMU=${HOME}/github/xemu/build/bin/xmega65.native

all: main hello

main: main.asm
	${BSA} main.asm

hello: hello_color_irq.asm
	${BSA} hello_color_irq.asm

flasher1: flasher1.asm
	${BSA} flasher1.asm

run_flasher1: flasher1
	${XEMU} -prgmode 64 -prg flasher1.prg


run: main
	${XEMU} -prgmode 64 -prg main.bin

run_hello: hello
	${XEMU} -prgmode 64 -prg hello.bin


clean:
	rm -fR main.prg main.lst *~
	rm -fR hello_color_irq.lst hello.prg
