// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

/*
macOS variant of the "llewe" keymap.

IMPORTANT: The macOS input source must be "German" (Deutsch), NOT
"German - Standard" (Deutsch Standard). The latter is the PC/Windows-style
layout and puts @ { } etc. on the Windows AltGr positions (Opt+Q, Opt+7,
Opt+0 ...), which this keymap does not follow.

The host is expected to run the German (ISO) macOS layout. The base key
positions of the German macOS layout are identical to the German PC layout,
so keymap_german.h (pulled in by the userspace) still describes them
correctly. Only the Option/AltGr plane differs:

    char   Win/Linux DE   macOS DE
    @      AltGr+Q        Opt+L
    ~      AltGr++        Opt+N   (dead key)
    \      AltGr+ss       Shift+Opt+7
    |      AltGr+<        Opt+7
    {      AltGr+7        Opt+8
    }      AltGr+0        Opt+9
    [      AltGr+8        Opt+5
    ]      AltGr+9        Opt+6

< and > are remapped from KC_NUBS to KC_GRV (and ^/° the other way) for
macOS, see german_mac_iso.h. This matches macOS classifying ortholinear
boards as ANSI, where the German layout moves < and > to the key left of 1.

Because the userspace hardcodes the PC sequences for CU_BSLS, this keymap
uses its own LL_BSLS instead.
*/

#include QMK_KEYBOARD_H

#ifdef GERMAN_MAC_ISO
#include "keymap_german_mac_iso.h"
#include "german_mac_iso.h"
#include "sendstring_german_mac_iso.h"
#else
#include "keymap_german.h"
#include "sendstring_german.h"
#endif
#include "llewe.h"
#include "llewe_common.h"
