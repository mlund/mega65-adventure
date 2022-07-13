// Copyright (C) 2022 Mikael Lund
//
// This program is free software; you can redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation; either version 3 of the
// License, or (at your option) any later version. This program is distributed in the hope that it
// will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with this program;
// if not, see http://www.gnu.org/licenses/gpl-3.0

// see e.g. KickC header files:
// https://gitlab.com/camelot/kickc/-/tree/master/src/main/kc/include
pub const SID: *mut u8 = (0xd400) as *mut u8;
pub const SID_ENTROPY: *mut u8 = (0xd41b) as *mut u8;
pub const BORDER_COLOR: *mut u8 = (0xd020) as *mut u8; // Border color
pub const SCREEN_COLOR: *mut u8 = (0xd021) as *mut u8; // Border color
pub const RED_PALETTE: *mut u8 = (0xd100) as *mut u8; // Red component
pub const GREEN_PALETTE: *mut u8 = (0xd200) as *mut u8; // Green component
pub const BLUE_PALETTE: *mut u8 = (0xd300) as *mut u8; // Blue component
pub const COLOUR_RAM: *mut u8 = (0xd800) as *mut u8; // Red background component
pub const VICII_SCREEN: *mut u8 = (0x0400) as *mut u8; // Start of screen ram
pub const VICIII_KEY: *mut u8 = (0xd02f) as *mut u8;
pub const VICIV_CONTROLA: *mut u8 = (0xd030) as *mut u8;
pub const VICIV_CONTROLB: *mut u8 = (0xd031) as *mut u8;
pub const VICIV_CONTROLC: *mut u8 = (0xd054) as *mut u8;

#[macro_export]
macro_rules! peek {
    ($address:expr) => {{
        #[allow(unused_unsafe)]
        unsafe {
            core::ptr::read_volatile($address)
        }
    }};
}

#[macro_export]
macro_rules! poke {
    ($address:expr, $value:expr) => {{
        #[allow(unused_unsafe)]
        unsafe {
            core::ptr::write_volatile($address, $value);
        }
    }};
}

#[macro_export]
macro_rules! add {
    ($value1:expr, $value2:expr) => {{
        $value1.wrapping_add($value2)
    }};
}

#[macro_export]
macro_rules! sub {
    ($value1:expr, $value2:expr) => {{
        $value1.wrapping_sub($value2)
    }};
}

/** Random number in the interval [0:255] w. entropy from SID register */
#[macro_export]
macro_rules! rand8 {
    () => {{
        peek!(SID_ENTROPY)
    }};
}

/** www.atarimagazines.com/compute/issue72/random_numbers.php */
pub unsafe fn start_sid_random_generator() {
    poke!(SID.offset(0x0e), 0xff);
    poke!(SID.offset(0x0f), 0xff);
    poke!(SID.offset(0x12), 0x80);
}


