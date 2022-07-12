/*****************************************************************************\
** plasma test program for cc65.                                             **
** Modified: Run to c64 mode on MEGA65                                       **
**                                                                           **
** (w)2001 by groepaz                                                        **
**                                                                           **
** Cleanup and porting by Ullrich von Bassewitz.                             **
**                                                                           **
\*****************************************************************************/

#include <stdint.h>
#include <stdlib.h>

#ifdef __clang__

#include "_6526.h"
#include "_vic2.h"
#include <stdio.h>
#define RAND_MAX 0x7FFF
#define VIC (*(volatile struct __vic2 *)0xd000)
#define CIA1 (*(volatile struct __6526 *)0xdc00)
#define CIA2 (*(volatile struct __6526 *)0xdd00)
#define cputc(letter) __putchar(letter)

#else

#include <conio.h>
/* Use static local variables for speed */
#pragma static-locals (1);
 
#endif

#define POKE(addr, val) (*(volatile uint8_t *)(addr)) = val
#define PEEK(addr) (*(volatile uint8_t *)(addr))
#define SCREEN1 0xe000
#define SCREEN2 0xe400
#define CHARSET 0xe800
#define VICII_SCREEN 0x0400
#define VICIII_KEY 0xd02f
#define VICIV_CONTROLA 0xd030
#define VICIV_CONTROLB 0xd031
#define VICIV_CONTROLC 0xd054

/* Values for the VIC address register to switch between the two pages */
#define PAGE1 ((SCREEN1 >> 6) & 0xF0) | ((CHARSET >> 10) & 0x0E)
#define PAGE2 ((SCREEN2 >> 6) & 0xF0) | ((CHARSET >> 10) & 0x0E)

static const uint8_t sinustable[0x100] = {
    0x80, 0x7d, 0x7a, 0x77, 0x74, 0x70, 0x6d, 0x6a, 0x67, 0x64, 0x61, 0x5e,
    0x5b, 0x58, 0x55, 0x52, 0x4f, 0x4d, 0x4a, 0x47, 0x44, 0x41, 0x3f, 0x3c,
    0x39, 0x37, 0x34, 0x32, 0x2f, 0x2d, 0x2b, 0x28, 0x26, 0x24, 0x22, 0x20,
    0x1e, 0x1c, 0x1a, 0x18, 0x16, 0x15, 0x13, 0x11, 0x10, 0x0f, 0x0d, 0x0c,
    0x0b, 0x0a, 0x08, 0x07, 0x06, 0x06, 0x05, 0x04, 0x03, 0x03, 0x02, 0x02,
    0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x03,
    0x03, 0x04, 0x05, 0x06, 0x06, 0x07, 0x08, 0x0a, 0x0b, 0x0c, 0x0d, 0x0f,
    0x10, 0x11, 0x13, 0x15, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24,
    0x26, 0x28, 0x2b, 0x2d, 0x2f, 0x32, 0x34, 0x37, 0x39, 0x3c, 0x3f, 0x41,
    0x44, 0x47, 0x4a, 0x4d, 0x4f, 0x52, 0x55, 0x58, 0x5b, 0x5e, 0x61, 0x64,
    0x67, 0x6a, 0x6d, 0x70, 0x74, 0x77, 0x7a, 0x7d, 0x80, 0x83, 0x86, 0x89,
    0x8c, 0x90, 0x93, 0x96, 0x99, 0x9c, 0x9f, 0xa2, 0xa5, 0xa8, 0xab, 0xae,
    0xb1, 0xb3, 0xb6, 0xb9, 0xbc, 0xbf, 0xc1, 0xc4, 0xc7, 0xc9, 0xcc, 0xce,
    0xd1, 0xd3, 0xd5, 0xd8, 0xda, 0xdc, 0xde, 0xe0, 0xe2, 0xe4, 0xe6, 0xe8,
    0xea, 0xeb, 0xed, 0xef, 0xf0, 0xf1, 0xf3, 0xf4, 0xf5, 0xf6, 0xf8, 0xf9,
    0xfa, 0xfa, 0xfb, 0xfc, 0xfd, 0xfd, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfd, 0xfd, 0xfc, 0xfb, 0xfa,
    0xfa, 0xf9, 0xf8, 0xf6, 0xf5, 0xf4, 0xf3, 0xf1, 0xf0, 0xef, 0xed, 0xeb,
    0xea, 0xe8, 0xe6, 0xe4, 0xe2, 0xe0, 0xde, 0xdc, 0xda, 0xd8, 0xd5, 0xd3,
    0xd1, 0xce, 0xcc, 0xc9, 0xc7, 0xc4, 0xc1, 0xbf, 0xbc, 0xb9, 0xb6, 0xb3,
    0xb1, 0xae, 0xab, 0xa8, 0xa5, 0xa2, 0x9f, 0x9c, 0x99, 0x96, 0x93, 0x90,
    0x8c, 0x89, 0x86, 0x83};

/*
 * Tell SID to start generating noise waveform
 * https://www.atarimagazines.com/compute/issue72/random_numbers.php
 */
void start_sid_random_generator() {
  POKE(0xd40e, 0xff);
  POKE(0xd40f, 0xff);
  POKE(0xd412, 0x80);
}

/** Two byte pseudo random number generator using SID register */
uint16_t rand_word() {
  uint16_t r;
  do {
    r = (uint16_t)((uint16_t)PEEK(0xd41b) << 8 | (uint16_t)PEEK(0xd41b));
  } while (r > RAND_MAX);
  return r;
}

uint8_t c1A = 0, c1B = 0;
uint8_t c2A = 0, c2B = 0;

static void doplasma(register uint8_t *scrn) {
  uint8_t xbuf[40];
  uint8_t ybuf[25];
  uint8_t c1a, c1b;
  uint8_t c2a, c2b;
  register uint8_t i, ii;

  c1a = c1A;
  c1b = c1B;
  for (ii = 0; ii < 25; ++ii) {
    ybuf[ii] = (sinustable[c1a] + sinustable[c1b]);
    c1a += 4;
    c1b += 9;
  }
  c1A += 3;
  c1B -= 5;
  c2a = c2A;
  c2b = c2B;
  for (i = 0; i < 40; ++i) {
    xbuf[i] = (sinustable[c2a] + sinustable[c2b]);
    c2a += 3;
    c2b += 7;
  }
  c2A += 2;
  c2B -= 3;
  for (ii = 0; ii < 25; ++ii) {
    /* Unrolling the following loop will give a speed increase of
    ** nearly 100% (~24fps), but it will also increase the code
    ** size a lot.
    */
    for (i = 0; i < 40; ++i, ++scrn) {
      *scrn = (xbuf[i] + ybuf[ii]);
    }
  }
}

void makechar(void) {
  static const uint8_t bittab[8] = {0x01, 0x02, 0x04, 0x08,
                                   0x10, 0x20, 0x40, 0x80};
  uint8_t i, ii, b, s;
  unsigned c;

  for (c = 0; c < 0x100; ++c) {
    s = sinustable[c];
    for (i = 0; i < 8; ++i) {
      b = 0;
      for (ii = 0; ii < 8; ++ii) {
        if ((rand_word() & 0xFFu) > s) {
          b |= bittab[ii];
        }
      }
      ((volatile uint8_t *)CHARSET)[(c * 8) + i] = b;
    }
    if ((c & 0x07) == 0) {
      cputc('.');
    }
  }
}

int main() {
  uint8_t block;
  start_sid_random_generator();
  makechar();

  /* Move the VIC 16K block */
  block = PEEK(&CIA2.pra);
  POKE(&CIA2.pra, (block & 0xFC) | ((SCREEN1 >> 14) ^ 0x03));

  while (1) {
    /* Build page 1, then make it visible */
    doplasma((uint8_t *)SCREEN1);
    POKE(&VIC.addr, PAGE1);

    /* Build page 2, then make it visible */
    doplasma((uint8_t *)SCREEN2);
    POKE(&VIC.addr, PAGE2);
  }

  return EXIT_SUCCESS;
}
