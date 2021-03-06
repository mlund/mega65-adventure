// Copyright (C) 2022 Mikael Lund
//
// This program is free software; you can redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation; either version 3 of the
// License, or (at your option) any later version. This program is distributed in the hope that it
// will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with this program;
// if not, see http://www.gnu.org/licenses/gpl-3.0

#![no_std]

pub mod mega65;
use core::ptr::write_bytes;
use mega65::*;

/// Greeting text in petscii encoding. @todo translate from ascii
const GREETING: [u8; 23] = [
    0x12, 0x15, 0x13, 0x14, 0x20, 0x13, 0x01, 0x19, 0x13, 0x20, 0x08, 0x05, 0x0c, 0x0c, 0x0f, 0x20,
    0xd, 0x5, 0x7, 0x1, 0x36, 0x35, 0x21,
];

/// Enable MEGA65 features c.f. deft's raster65 demo#!
unsafe fn enable_mega65() {
    poke!(VICIII_KEY, 0x47);
    poke!(VICIII_KEY, 0x53);
    poke!(VICIV_CONTROLB, peek!(VICIV_CONTROLB) | 0x40);
    poke!(VICIV_CONTROLC, peek!(VICIV_CONTROLC) | 0x40);

    // @todo opcode "nop" unrecognized by llvm, see https://llvm-mos.org/wiki/C_Inline_Assembly
    core::arch::asm!(""); // "nop"
}

/// Fill entire screen with a single character, assuming 40 x 25 text mode
/// @todo Use DMA copy instead?
unsafe fn fill_screen(character: u8) {
    write_bytes(VICII_SCREEN, character, 40 * 25);
}

/// Copy a piece of text to screen ram
fn write_text(xpos: u16, ypos: u16, buffer: &[u8]) {
    let mut offset = xpos + ypos * 40;
    for character in buffer {
        poke!(VICII_SCREEN.offset(offset as isize), *character);
        offset += 1;
    }
}

/// Increment screen border color
fn increment_border_color() {
    let color = peek!(BORDER_COLOR);
    poke!(BORDER_COLOR, color + 1);
}

#[no_mangle]
pub extern "C" fn rusty_main() {
    unsafe {
        enable_mega65();
        fill_screen(0x20);
        write_text(8, 12, &GREETING);
        loop {
            increment_border_color();
        }
    }
}
