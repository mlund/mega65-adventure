;coded by Graham/Oxyron

    *= $1000
.LOAD $1000

    lda #$7f
    sta $dc0d
    and $d011
    sta $d011
    lda #$32
    sta $d012

    sei
    lda #<irq
    sta $0314
    lda #>irq
    sta $0315
    lda #$01
    sta $d01a
    cli
    rts

irq:
    lda #$ff
    sta $d019

    ldx #$05
d   dex
    bne d

    ldx #$00
c   ldy #$08
a   lda colors,x
    sta $d020
    sta $d021
    inx
    dey
    beq c

    txa
    ldx #$07
b   dex
    bne b
    tax

    cpx #$8c
    bcc a

    jmp $ea34

colors:
    .byte $09,$02,$08,$0a,$0f,$07,$01,$07,$0f,$0a,$08,$02,$09,$00
    .byte $06,$04,$0e,$05,$03,$0d,$01,$0d,$03,$05,$0e,$04,$06,$00
    .byte $09,$02,$08,$0a,$0f,$07,$01,$07,$0f,$0a,$08,$02,$09,$00
    .byte $06,$04,$0e,$05,$03,$0d,$01,$0d,$03,$05,$0e,$04,$06,$00
    .byte $09,$02,$08,$0a,$0f,$07,$01,$07,$0f,$0a,$08,$02,$09,$00
    .byte $06,$04,$0e,$05,$03,$0d,$01,$0d,$03,$05,$0e,$04,$06,$00
    .byte $09,$02,$08,$0a,$0f,$07,$01,$07,$0f,$0a,$08,$02,$09,$00
    .byte $06,$04,$0e,$05,$03,$0d,$01,$0d,$03,$05,$0e,$04,$06,$00
    .byte $09,$02,$08,$0a,$0f,$07,$01,$07,$0f,$0a,$08,$02,$09,$00
    .byte $06,$04,$0e,$05,$03,$0d,$01,$0d,$03,$05,$0e,$04,$06,$00

.STORE $1000, $2000, "rasterbars3.o"

