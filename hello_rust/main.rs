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

mod mega65;
use mega65::*;

const GREETING: [u8; 23] = [0x12, 0x15, 0x13, 0x14, 0x20, 0x13, 0x01, 0x19, 0x13, 0x20, 0x08,
0x05, 0x0c, 0x0c, 0x0f, 0x20, 0xd, 0x5, 0x7, 0x1, 0x36, 0x35, 0x21];

fn write_text(xpos: u16, ypos: u16, buffer: &[u8]) {
    let mut offset = xpos + ypos*40;
    for character in buffer {
        poke!(VICII_SCREEN.offset(offset as isize), *character);
        offset += 1;
    }
}

fn increment_border_color() {
    let color = peek!(BORDER_COLOR);
    poke!(BORDER_COLOR, color+1);
}

fn fill_screen(character: u8) {
    for offset in 0..40*25 {
        poke!(VICII_SCREEN.offset(offset as isize), character);
    }
}

/*
 * Enable MEGA65 features c.f. deft's raster65 demo
 */
fn enable_mega65() {
    poke!(VICIII_KEY, 0x47);
    poke!(VICIII_KEY, 0x53);
    poke!(VICIV_CONTROLB, peek!(VICIV_CONTROLB) | 0x40);
    poke!(VICIV_CONTROLC, peek!(VICIV_CONTROLC) | 0x40);
}


#[no_mangle]
pub extern "C" fn rusty_main() {
    enable_mega65();
    fill_screen(0x20);
    write_text(8, 12, &GREETING);
    loop {
        increment_border_color();
    }
}
