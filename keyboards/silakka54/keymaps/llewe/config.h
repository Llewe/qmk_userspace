/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Each half knows its role (left/right) from EE_HANDS. Simplest flashing:
// use the CI artifacts silakka54_llewe_left.uf2 / silakka54_llewe_right.uf2
// (built with -e HANDEDNESS=left|right, see rules.mk) - each forces its role
// on every boot. Or flash each half once with
//   qmk flash -kb silakka54 -km llewe -bl uf2-split-left   (left halves)
//   qmk flash -kb silakka54 -km llewe -bl uf2-split-right  (right halves)
// The half connected to USB is then the master automatically, so the same
// firmware works with USB on the left or the right side.
#define EE_HANDS

// The six-thumb chord needs more time than the default 50ms to land.
#define COMBO_TERM 150

// send_unicode_string()/UCIS switch between macOS "Unicode Hex Input" and the
// Linux mode at runtime (see os_toggle() in llewe_common.h of this keymap).
#define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS, UNICODE_MODE_LINUX
