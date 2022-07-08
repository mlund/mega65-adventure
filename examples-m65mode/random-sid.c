// Random numbers using the SID chip
// https://www.atarimagazines.com/compute/issue72/random_numbers.php

#include <stdio.h>

#  define POKE(addr,val) (*(volatile unsigned char*)(addr)) = val
#  define PEEK(addr) (*(volatile unsigned char*)(addr))

void start_sid_asm() {
     asm volatile (
        "lda 0xff\n"
        "sta 0xd40e\n"
        "sta 0xd40f\n"
        "lda 0x80\n"
        "sta $d412"
        );
}

void start_sid_c() {
    POKE(0xd40e, 0xff);
    POKE(0xd40f, 0xff);
    POKE(0xd412, 0x80);
}

uint8_t random_byte() {
    return PEEK(0xd41b);
}

uint16_t random_word() {
    return 0;
}

int main() {
    int i;
    start_sid_c();
    printf("RANDOM BYTES");
    for (i=0; i<20; i++) {
        printf("%d ", random_byte());
    }
}
