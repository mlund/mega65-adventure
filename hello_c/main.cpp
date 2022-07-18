#include <cstdint>
using byte = uint8_t;

#define PEEK(address) (*(uint8_t*)(address))
#define POKE(address, value) *(uint8_t*)(address) = (value)

typedef void (*IRQ_TYPE)(void);
IRQ_TYPE* const KERNAL_IRQ = (IRQ_TYPE*)0x0314;

void irq() asm("IRQ"); // enable asm access
void irq2() asm("IRQ2"); // enable asm access

void loop_forever()
{
    while (true) {
        asm volatile("");
    }
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
void raster_wait_interrupt(IRQ_TYPE irq)
{
    asm volatile(
        "sei\n"
        "lda #$7f\n" // turn off the cia interrupts
        "sta $dc0d\n"
        "lda $d01a\n" // enable raster irq
        "ora #$01\n"
        "sta $d01a\n"
        "lda $d011\n" // clear high bit of raster line
        "and #$7f\n"
        "sta $d011\n"
        "lda #100\n" // line number to go off at
        "sta $d012\n" // low byte of raster line
        ::
            : "a");
    *KERNAL_IRQ = irq2;
    asm volatile("cli");
}

int main()
{
    // simple_interrupt(&irq);
    raster_wait_interrupt(&irq);
    // loop_forever();
}

void irq()
{
    auto color = PEEK(0xd020);
    POKE(0xd020, color + 1);
    asm volatile("jmp $ea31");
}

int mode = 0;

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
