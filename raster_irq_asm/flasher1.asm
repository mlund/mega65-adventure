;
; this program causes the border to flash 60 times per second
; http://www.antimon.org/dl/c64/code/raster.txt
;
*=$1000
.LOAD $1000

sei                           ; disable interrupts
lda #<intcode                 ; get low byte of target routine
sta 788                       ; put into interrupt vector
lda #>intcode                 ; do the same with the high byte
sta 789
cli                           ; re-enable interrupts
rts                           ; return to caller

intcode:
inc $d020                     ; change border colour
jmp $ea31

.STORE $1000, $2000, "flasher1.o"

