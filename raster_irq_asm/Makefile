BSA=${HOME}/bin/bsa
EXOMIZER=${HOME}/bin/exomizer
XEMU="${HOME}/github/xemu/build/bin/xmega65.native -prgmode 64 -prg "
VICE=/opt/homebrew/opt/vice/bin/x64sc

all: c64wiki hello flasher1 rasterbars3

# -------------------
#
c64wiki: c64wiki.asm
	${BSA} c64wiki.asm
	${EXOMIZER} sfx 0x1000 c64wiki.o -o c64wiki.prg

run: c64wiki
	${VICE} c64wiki.prg

# -------------------
#
hello: hello_color_irq.asm
	${BSA} hello_color_irq.asm
	${EXOMIZER} sfx 0x1000 hello.o -o hello.prg

run_hello: hello
	${VICE} hello.prg

# -------------------

flasher1: flasher1.asm
	${BSA} flasher1.asm
	${EXOMIZER} sfx 0x1000 flasher1.o -o flasher1.prg

run_flasher1: flasher1
	${VICE} flasher1.prg

# -------------------
#
rasterbars3: rasterbars3.asm
	${BSA} rasterbars3.asm
	${EXOMIZER} sfx 0x1000 rasterbars3.o -o rasterbars3.prg

run_rasterbars3: rasterbars3
	${VICE} rasterbars3.prg

# -------------------

clean:
	rm -fR *.prg *.lst *.o *~
	rm -fR hello_color_irq.lst hello.prg
