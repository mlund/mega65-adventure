#include <cstdint>
using byte = uint8_t;

#define PEEK(address) (*(uint8_t*)(address))
#define POKE(address, value) *(uint8_t*)(address) = (value)

typedef void (*IRQ_TYPE)(void);
IRQ_TYPE* const KERNAL_IRQ = (IRQ_TYPE*)0x0314;

void loop_forever()
{
    while (true) {
        asm volatile("");
    }
}

//void irq() asm("IRQ"); // enable asm access
void irq()
{
//    asm volatile(R"(
//        lda $d019
//        sta $d019
//        lda #100
//        sta $d012
//        jmp $ea31
//    )" ::: "a");
    POKE(0xd019, 0xff);
    auto raster_line = PEEK(0xd012);
    if (raster_line > 50) {
        POKE(0xd020, 2);
    } else {
        POKE(0xd020, 3);
    }

    asm volatile("jmp $ea34");
}

//void irq2() asm("IRQ2"); // enable asm access
void irq2()
{
    auto color = PEEK(0xd020);
    POKE(0xd020, color + 1);
    asm volatile(R"(
        lda $d019
        sta $d019
        lda #100
        sta $d012
        jmp $ea31
    )" ::: "a");
}


/*
 * simplest possible interrupt(?)
 */
void simple_interrupt(IRQ_TYPE irq)
{
    asm volatile("sei");
    *KERNAL_IRQ = irq;
    asm volatile("cli");
}

/*
 * interrupt waiting for raster line
 */
void raster_wait_interrupt(IRQ_TYPE irq, const std::uint8_t raster_line)
{
    asm volatile(R"(
        sei
        lda 0b01111111 // turn off the cia interrupts
        sta $dc0d
        lda $d01a // enable raster irq
        ora #$01
        sta $d01a
        lda $d011 // clear high bit of raster line
        and #$7f
        sta $d011
        )" :::"a");

    POKE(0xd012, raster_line); // triggering raster line 
    *KERNAL_IRQ = irq2;
    asm volatile("cli");
}

int main()
{
    // simple_interrupt(&irq);
    raster_wait_interrupt(&irq, 50);
    // loop_forever();
}

int mode = 0;


