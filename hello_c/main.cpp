#include <cstdint>
using byte = uint8_t;

#define PEEK(address) (*(uint8_t*)(address))
#define POKE(address, value) *(uint8_t*)(address) = (value)

typedef void (*IRQ_TYPE)(void);
IRQ_TYPE* const KERNAL_IRQ = (IRQ_TYPE*)0x0314;
void irq() asm("IRQ"); // enable asm access

void loop_forever()
{
    while (true) {
        asm volatile("");
    }
}

/** simplest possible interrupt(?) */
void simple_interrupt(IRQ_TYPE irq)
{
    asm volatile("sei");
    *KERNAL_IRQ = irq;
    asm volatile("cli");
}

int main()
{
    simple_interrupt(&irq);
    loop_forever();
}

void irq()
{
    auto color = PEEK(0xd020);
    POKE(0xd020, color + 1);
    asm volatile("jmp $ea31");
}
