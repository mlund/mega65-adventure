// Randomness from the SID chip:
// https://www.atarimagazines.com/compute/issue72/random_numbers.php
//
// Will compile with:
//
//   llvm-mos
//   cc65
//
#include <stdint.h>
#include <stdio.h>

#define POKE(addr, val) (*(volatile unsigned char *)(addr)) = val
#define PEEK(addr) (*(volatile unsigned char *)(addr))
#define RAND_MAX 0x7FFF

void start_sid_asm() {
#ifdef __clang__
  asm volatile("lda 0xff\n"
               "sta 0xd40e\n"
               "sta 0xd40f\n"
               "lda 0x80\n"
               "sta $d412");
#else
  asm("lda #$ff");
  asm("sta $d40e");
  asm("sta $d40f");
  asm("lda #$80");
  asm("sta $d412");
#endif
}

void start_sid_c() {
  POKE(0xd40e, 0xff);
  POKE(0xd40f, 0xff);
  POKE(0xd412, 0x80);
}

uint8_t rand_byte() { return PEEK(0xd41b); }

uint16_t rand_word() {
  uint16_t r;
  do {
    r = (uint16_t)((uint16_t)rand_byte() << 8 | (uint16_t)rand_byte());
  } while (r > RAND_MAX);
  return r;
}

int main() {
  int i;
  start_sid_asm();

  printf("RANDOM BYTES:");
  for (i = 0; i < 20; i++) {
    printf("%d ", rand_byte());
  }

  printf("RANDOM WORDS:");
  for (i = 0; i < 20; i++) {
    printf("%d ", rand_word());
  }

  return 0;
}
