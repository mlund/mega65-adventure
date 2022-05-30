// Copyright (C) 2022 Mikael Lund
//
// This program is free software; you can redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation; either version 3 of the
// License, or (at your option) any later version. This program is distributed in the hope that it
// will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with this program;
// if not, see http://www.gnu.org/licenses/gpl-3.0

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

// see e.g. KickC header files:
// https://gitlab.com/camelot/kickc/-/tree/master/src/main/kc/include
pub const BORDER_COLOR: *mut u8 = (0xd020) as *mut u8; // Border color
pub const VICII_SCREEN: *mut u8 = (0x0400) as *mut u8; // Start of screen ram
pub const VICIII_KEY: *mut u8 = (0xd02f) as *mut u8;
pub const VICIV_CONTROLA: *mut u8 = (0xd030) as *mut u8;
pub const VICIV_CONTROLB: *mut u8 = (0xd031) as *mut u8;
pub const VICIV_CONTROLC: *mut u8 = (0xd054) as *mut u8;
