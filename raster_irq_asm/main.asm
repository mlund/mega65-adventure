; https://www.c64-wiki.com/wiki/Raster_interrupt
*=$1000
.LOAD $1000
Init       sei
           LDA %01111111       ; switch off interrupt signals from CIA-1
           STA $DC0D

           AND $D011            ; clear most significant bit of VIC's raster register
           STA $D011

           LDA $DC0D            ; acknowledge pending interrupts from CIA-1
           LDA $DD0D            ; acknowledge pending interrupts from CIA-2

           LDA #210             ; set rasterline where interrupt shall occur
           STA $D012

           LDA #<Irq            ; set interrupt vectors, pointing to interrupt service routine below
           STA $0314
           LDA #>Irq
           STA $0315

           LDA %00000001       ; enable raster interrupt signals from VIC
           STA $D01A

           CLI                  ; clear interrupt flag, allowing the CPU to respond to interrupt requests
           RTS

Irq:       LDA #$7
           STA $D020            ; change border colour to yellow

           LDX #$90             ; empty loop to do nothing for just under half a millisecond
Pause:     DEX
           BNE Pause

           LDA #$0
           STA $D020            ; change border colour to black

           ASL $D019            ; acknowledge the interrupt by clearing the VIC's interrupt flag

           JMP $EA31            ; jump into KERNAL's standard interrupt service routine to handle keyboard scan, cursor display etc.
.STORE $1000, $2000, "main.o"
